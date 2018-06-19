/*
 * Copyright (c) 2015 OpenALPR Technology, Inc.
 * Open source Automated License Plate Recognition [http://www.openalpr.com]
 *
 * This file is part of OpenALPR. It has been modified by ATECRESA to allow socket communication.
*/

#include <cstdio>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "tclap/CmdLine.h"
#include "support/filesystem.h"
#include "support/timing.h"
#include "support/platform.h"
#include "video/videobuffer.h"
#include "motiondetector.h"
#include "alpr.h"

// SOCKET LIBRARIES
#include <windows.h>

using namespace alpr;

const std::string MAIN_WINDOW_NAME = "ALPR main window";

WSADATA wsaData;
SOCKET socketFd, serverSocketFd;
int stsize = sizeof(struct sockaddr);
struct sockaddr_in server, client;

int PORT = 1234, CAMERA = 1;
std::string CAMERA_ADDRESS = "";
const std::string SERVER_IP = "127.0.0.1";
const std::string TAKE_PICTURE_SIGNAL = "Z";
const std::string DEFAULT_LICENSE_PLATE = "NO_LEGIBLE";

/** Function Headers */
std::string detectandshow(Alpr* alpr, cv::Mat frame, std::string region, bool writeJson);
void sendLicensePlate(std::string license_plate);
int openSocket();
std::string listenToSocket();
std::string templatePattern = "es";

// This boolean is set to false when the user hits terminates (e.g., CTRL+C )
// so we can end infinite loops for things like video processing.
bool program_active = true;

int main( int argc, const char** argv )
{
    std::string configFile = "";
    std::string country;
    bool outputJson = false;
    bool debug_mode = false;

    // TCLAP is a CmdLine utility to help parsing the arguments that the program receives.
    TCLAP::CmdLine cmd("OpenAlpr Command Line Utility", ' ', Alpr::getVersion());

    // Available commands
    TCLAP::ValueArg<std::string> countryCodeArg("c","country","Country code to identify (either us for USA or eu for Europe).  Default=eu",false, "eu" ,"country_code");
    TCLAP::ValueArg<std::string> configFileArg("","config","Path to the openalpr.conf file", false, "config\\openalpr.conf","config_file");
    TCLAP::ValueArg<int> portArg("p","port","Port to open server.  Default = 1234", false, 1234, "port");
    TCLAP::ValueArg<std::string> cameraAddressArg("a","address","Address to the ip camera", false, "", "address");
    TCLAP::ValueArg<int> cameraArg("","camera","Default video camera by usb = 0", false, 0, "camera");

    TCLAP::SwitchArg jsonSwitch("j","json","Output recognition results in JSON format.  Default=off", cmd, false);
    TCLAP::SwitchArg debugSwitch("","debug","Enable debug output.  Default=off", cmd, false);

    std::string runtimeDir = "runtime_data";
    try
    {
        // We must add the value args to the cmd, in order to allow it to parse them.
        cmd.add(configFileArg);
        cmd.add(countryCodeArg);
        cmd.add(portArg);
        cmd.add(cameraAddressArg);
        cmd.add(cameraArg);

        // We must parse all the arguments or we will get the default values!
        cmd.parse( argc, argv );

        configFile = configFileArg.getValue();
        country = countryCodeArg.getValue();
        debug_mode = debugSwitch.getValue();
        outputJson = jsonSwitch.getValue();

        PORT = portArg.getValue();
        CAMERA = cameraArg.getValue();
        CAMERA_ADDRESS = cameraAddressArg.getValue();
    }
    catch (TCLAP::ArgException &e)    // catch any exceptions
    {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
        return 1;
    }

    Alpr alpr(country, configFile, runtimeDir);
    alpr.setTopN(10);
    alpr.setDefaultRegion("es");

    if (alpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
        return 1;
    }

    // OPEN SOCKET
    std::cout << "PORT " << PORT << " added!\n";
    if (openSocket() < 0) {
        std::cerr << "Error opening socket. Please try again with a valid port and server listening.\n";
        return -1;
    }

    // Video camera to use
    cv::VideoCapture cap(CAMERA);
    if (CAMERA_ADDRESS != "") { // IP Camera Enabled
        cap = cv::VideoCapture(CAMERA_ADDRESS);
        std::cout << "Setting new Camera address: " << CAMERA_ADDRESS << "\n";
    }

    cv::Mat frame;
    // Infinite loop, always listening to the socket default signal.
    while (true) {
        // Automatic Input by socket. Loop until the signal is received
        std::string inputCommand = "";
        do {
            inputCommand = listenToSocket();
        } while (inputCommand[0] != TAKE_PICTURE_SIGNAL[0]);

        bool tookPicture = cap.read(frame);
        if (!tookPicture) {
            std::cout << "ERROR TAKING PICTURE...\n";
            continue;
        }
        else {
            std::cout << "TAKING PICTURE...\n";
        }

        // Write last-image for debugging
        cv:imwrite("last-image.jpg", frame);

        std::string bestLicensePlate = detectandshow(&alpr, frame, "", outputJson) + "\n";
        sendLicensePlate(bestLicensePlate);
    }
}

// Method that get two socket file descriptors, the server one and the client one.
int openSocket()
{
    if (WSAStartup(MAKEWORD(1,0),&wsaData)) {
        printf("Socket creation error\n");
        return -1;
    }

    struct hostent *hp;
    hp = (struct hostent *) gethostbyname(SERVER_IP.c_str());
    if(!hp){
        printf("Server not found...");
        WSACleanup();
        return -1;
    }

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFd == INVALID_SOCKET) {
        printf("Error creating socket\n");
        WSACleanup();
        return -1;
    }

    memset(&server, 0, sizeof(server));
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(PORT);

    if(bind(socketFd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        printf("Error associating the IP port\n");
        closesocket(socketFd);
        WSACleanup();
        return -1;
    }

    if(listen(socketFd, 1) == SOCKET_ERROR){
        printf("Error during communication enable\n");
        closesocket(socketFd);
        WSACleanup();
        return -1;
    }

    serverSocketFd = accept(socketFd,(struct sockaddr *)&client, &stsize);
    if(serverSocketFd == INVALID_SOCKET){
        printf("Error accepting communication\n");
        closesocket(socketFd);
        WSACleanup();
        return -1;
    }

    std::cout << "Client connected\n";
    return 0;
}

// Method that listen to a socket and get the message!
std::string listenToSocket()
{
    char buffer[1024] = {0};
    int read_size = recv(serverSocketFd, buffer, sizeof(buffer), 0);
    if(read_size <= 0)
    {
        std::cout << "Client disconnected\n";
        serverSocketFd = accept(socketFd,(struct sockaddr *)&client, &stsize);
        if(serverSocketFd == INVALID_SOCKET){
            printf("Error accepting communication\n");
            closesocket(socketFd);
            WSACleanup();
            return "ERROR";
        }

        std::cout << "Client connected\n";
        return listenToSocket();
    }

    std::cout << "Message received: " << buffer << "\n";
    return std::string(buffer);
}

// Method that sends the license plate obtained by socket
void sendLicensePlate(std::string license_plate)
{
    send(serverSocketFd, license_plate.c_str(), license_plate.length(), 0);
    std::cout << "Message sent: " << license_plate << "\n";
}

// Method that uses the OPENALPR code to detect the licenseplate of the photo we captured.
std::string detectandshow( Alpr* alpr, cv::Mat frame, std::string region, bool writeJson)
{
    timespec startTime;
    getTimeMonotonic(&startTime);

    std::vector<AlprRegionOfInterest> regionsOfInterest;
    regionsOfInterest.push_back(AlprRegionOfInterest(0, 0, frame.cols, frame.rows));

    AlprResults results;
    bool gotResults = false;
    if (regionsOfInterest.size() > 0) {
        results = alpr -> recognize(frame.data, frame.elemSize(),
                                    frame.cols, frame.rows, regionsOfInterest);
        gotResults = true;
    }

    timespec endTime;
    getTimeMonotonic(&endTime);
    double totalProcessingTime = diffclock(startTime, endTime);
    std::cout << "Total Time to process image: " << totalProcessingTime << "ms." << std::endl;

    std::string bestLicensePlate = DEFAULT_LICENSE_PLATE;
    if (writeJson && gotResults)
    {
        std::cout << alpr->toJson( results ) << std::endl;
    }
    else if (gotResults)
    {
        for (int i = 0; i < results.plates.size(); i++)
        {
            std::cout << "plate" << i << ": " << results.plates[i].topNPlates.size() << " results";
            //std::cout << " -- Processing Time = " << results.plates[i].processing_time_ms << "ms.";
            std::cout << std::endl;

            if (results.plates[i].regionConfidence > 0)
                std::cout << "State ID: " << results.plates[i].region << " (" << results.plates[i].regionConfidence << "% confidence)" << std::endl;

            for (int k = 0; k < results.plates[i].topNPlates.size(); k++)
            {
                // Replace the multiline newline character with a dash
                std::string no_newline = results.plates[i].topNPlates[k].characters;
                std::replace(no_newline.begin(), no_newline.end(), '\n','-');

                std::cout << "    - " << no_newline << "\t confidence: " << results.plates[i].topNPlates[k].overall_confidence;
                if (templatePattern.size() > 0 || results.plates[i].regionConfidence > 0)
                    std::cout << "\t pattern_match: " << results.plates[i].topNPlates[k].matches_template;

                std::cout << std::endl;
                alpr::AlprPlate currentLicensePlate = results.plates[i].topNPlates[k];
                // The best license plate is the top one that matches the template.
                if ((bestLicensePlate == DEFAULT_LICENSE_PLATE) && currentLicensePlate.matches_template) {
                    bestLicensePlate = currentLicensePlate.characters;
                }
            }
            // If there wasn't any template, the best license plate is the first top plate.
            if ((bestLicensePlate == DEFAULT_LICENSE_PLATE) && (results.plates[i].topNPlates.size() > 0)) {
                bestLicensePlate = results.plates[i].topNPlates[0].characters;
            }
        }
    }

    return bestLicensePlate;
}
