//
//  main.cpp
//  MIE
//
//  Created by Bernardo Ferreira on 27/02/15.
//  Copyright (c) 2015 NovaSYS. All rights reserved.
//

#include "MIEClient.h"
#include "SSEClient.h"
#include "CashClient.hpp"
#include "PaillierCashClient.hpp"

using namespace cv;
using namespace std;

void printQueryResults (vector<QueryResult> queryResults) {
    for (int i = 0; i < std::min((int)queryResults.size(), 10); i++)
        LOGI("docId: %d score: %f\n", queryResults[i].docId, queryResults[i].score);
}

void printQueryResults (set<QueryResult,cmp_QueryResult> queryResults) {
    for (set<QueryResult,cmp_QueryResult>::iterator it = queryResults.begin(); it!=queryResults.end(); ++it)
        LOGI("docId: %d score: %f\n", (*it).docId, (*it).score);
}

void runMIEClientHolidayAdd() {
    LOGI("begin MIE Holiday Add!\n");
    MIEClient mie;
    timespec start = getTime();
    mie.addDocs("inriaHolidays","flickr_tags",1,1491,0);
    double total_time = diffSec(start, getTime());
    LOGI("%s total_time:%.6f\n",mie.printTime().c_str(),total_time);
}

void runMIEClientFlickrAdd() {
    LOGI("begin MIE Flickr Add!\n");
    MIEClient mie;
    timespec start = getTime();
    mie.addDocs("flickr_imgs", "flickr_tags",1,1000,0);
    double total_time = diffSec(start, getTime());
    LOGI("%s total_time:%.6f\n",mie.printTime().c_str(),total_time);
}

void runMIEClientIndex() {
    LOGI("begin MIE index!\n");
    MIEClient mie;
    timespec start = getTime();
    mie.index();
    double total_time = diffSec(start, getTime());
    LOGI("%s total_time:%.6f\n",mie.printTime().c_str(),total_time);
}

void runMIEClientHolidaySingleSearch() {
    LOGI("begin MIE index!\n");
    MIEClient mie;
    string imgPath = homePath;
    imgPath += "Datasets/inriaHolidays/100701.jpg";
    string textPath = homePath;
    textPath += "Datasets/flickr_tags/tags1.txt";
    vector<QueryResult> queryResults = mie.search(1, imgPath, textPath);
    printQueryResults(queryResults);
}

void runMIEClientFlickrSingleSearch() {
    LOGI("begin MIE index!\n");
    MIEClient mie;
    timespec start = getTime();
    string imgPath = homePath;
    imgPath += "Datasets/flickr_imgs/im1.jpg";
    string textPath = homePath;
    textPath += "Datasets/flickr_tags/tags1.txt";
    vector<QueryResult> queryResults = mie.search(1, imgPath, textPath);
    double total_time = diffSec(start, getTime());
    LOGI("%s total_time:%.6f\n",mie.printTime().c_str(),total_time);
    printQueryResults(queryResults);
}

void runMIEClientHolidayQueries() {
    LOGI("begin MIE Holiday Queries!\n");
    MIEClient mie;
    map<int,vector<QueryResult> > queries;
    char* imgPath = new char[120];
    char* textPath = new char[120];
    for (int i = 1; i <= 25000; i+=1) {
        bzero(imgPath, 120);
        bzero(textPath, 120);
        sprintf(imgPath, "%sDatasets/mirflickr/im%d.jpg", homePath, i);
        sprintf(textPath, "%sDatasets/mirflickr/meta/tags/tags%d.txt", homePath, i);
        queries[i] = mie.search(i, imgPath, textPath);
    }
    delete[] imgPath;
    delete[] textPath;
    string fName = homePath;
    fName += "Data/Client/MIE/mieHoliday.dat";
    printHolidayResults(fName, queries);
    LOGI("Search results writen to disk!\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void runCashClientHolidayAdd() {
    LOGI("begin Cash Holiday Add!\n");
    timespec start = getTime();
    CashClient cash;
    cash.train("inriaHolidays",1,1491);
    cash.addDocs("inriaHolidays","flickr_tags",1,1);
    double total_time = diffSec(start, getTime());
    LOGI("%s total_time:%.6f\n",cash.printTime().c_str(),total_time);
}

void runCashClientHolidayQueries() {
    LOGI("begin Cash Holiday Queries!\n");
    CashClient cash;
    cash.train("inriaHolidays",1,1491);
    map<int,vector<QueryResult> > queries;
    char* imgPath = new char[120];
    char* textPath = new char[120];
    for (int i = 100000; i <= 149900; i+=100) {
        bzero(imgPath, 120);
        bzero(textPath, 120);
        sprintf(imgPath, "/home/guilherme/Datasets/inria/%d.jpg", i);
        sprintf(textPath, "/home/guilherme/Datasets/mirflickr/meta/tags/tags%d.txt", i);
        queries[i] = cash.search(imgPath,textPath, true);
    }
    delete[] imgPath;
    delete[] textPath;
    string fName = homePath;
    fName += "Data/Client/Cash/cashHoliday.dat";
    printHolidayResults(fName, queries);
    LOGI("Search results writen to disk!\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void runCashClientFlickr(size_t files, size_t queries) {
    LOGI("begin Cash Flickr Add!\n");
    CashClient cash;
    cash.train("flickr_imgs", 1, files);

    timespec start = getTime();
    cash.addDocs("flickr_imgs","flickr_tags", 1, files);
    double total_time = diffSec(start, getTime());

    LOGI("%s\n",cash.printTime().c_str());
    LOGI("time adds (%lu imgs) %.6fs\n", files, total_time);
    LOGI("begin Cash Flickr Queries!\n");

    total_time = 0;
    char* imgPath = new char[120];
    char* textPath = new char[120];
    for (int i = 1; i <= queries; i+=1) {
        bzero(imgPath, 120);
        bzero(textPath, 120);
        sprintf(imgPath, "/home/guilherme/Datasets/mirflickr/im%d.jpg", i);
        sprintf(textPath, "/home/guilherme/Datasets/mirflickr/meta/tags/tags%d.txt", i);

        timespec start = getTime();
        vector<QueryResult> queryResults = cash.search(imgPath, textPath, true);
        total_time += diffSec(start, getTime());
        //LOGI("%s\n",cash.printTime().c_str());
        //printQueryResults(queryResults);
    }

    printf("time queries %lfs (avgd. %lu)\n", total_time / queries, queries);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    if(argc != 3) {
        printf("invalid args\n");
        exit(1);
    }

    size_t files = stoul(argv[1]);
    size_t queries = stoul(argv[2]);

    runCashClientFlickr(files, queries);
}


/*int main(int argc, const char * argv[]) {
    Mat image = imread("/Users/bernardo/Datasets/inriaHolidays/100000.jpg");
    SurfFeatureDetector detector;
    vector<KeyPoint> keypoints;
    detector.detect(image,keypoints);
    SurfDescriptorExtractor extractor;
    Mat descriptors;
    extractor.compute(image, keypoints, descriptors);
//    SBE(descriptors.cols);
    //lm distance
    int m = 2;
    int count = 0;
    for (int w = 0; w < descriptors.rows-1; w++) {
        float total = 0.0;
        for (int i = 0; i < descriptors.cols; i++) {
            const float x = descriptors.at<float>(w,i);
            const float y = descriptors.at<float>(w+1,i);
            total += pow(fabs(x -y), m);
        }
        total = pow(total,1.0/m);
        if (total < 0.5)
            count++;
    }
    printf("total descriptors:%d count:%d\n",descriptors.rows,count);

}*/
