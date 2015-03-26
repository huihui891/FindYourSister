// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_HANDLER
#define _H_JSON_HANDLER

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

namespace fys{

// helper class
class ImageSize
{
public:
    ImageSize();
    ImageSize(int nrows, int ncols);
    ~ImageSize();
    int nrows;
    int ncols;
};

class ImageRegion
{
public:
    ImageRegion();
    ImageRegion(int xmin, int xmax, int ymin, int ymax);
    ~ImageRegion();
    int xmin;
    int xmax;
    int ymin;
    int ymax;
};

class ImageObject
{
public:
    ImageObject(string name, int id, ImageRegion& region);
    ~ImageObject(); 
    string name;
    int id;
    ImageRegion region;
};

class ImageSample
{
public:
    ImageSample();
    ImageSample(int train, int validate, int test);
    ~ImageSample();
    int train;
    int validate;
    int test;
    int total;
};

// base class
class JsonHandler
{

public:
    JsonHandler(string filename);
    ~JsonHandler();
    void readJsonFile(); // open & read json file
    string getFileStr(); // return json file as string
    string getDocStr(rapidjson::StringBuffer& buffer); // return json document as string
    void updateStr(rapidjson::StringBuffer& buffer); // update this->jsonStr
    void writeJsonFile(); // open & write json file

    int getIntVal(const rapidjson::Value& doc, vector<string> position);
    void setIntVal(rapidjson::Value& doc, vector<string> position, int newVal);
    double getDoubleVal(const rapidjson::Value& doc, vector<string> position);
    void setDoubleVal(rapidjson::Value& doc, vector<string> position, double newVal);
    string getStrVal(const rapidjson::Value& doc, vector<string> position);
    void setStrVal(rapidjson::Value& doc, vector<string> position, string newVal);

private:
    string jsonFilename;
    string jsonStr;
};


// features class
class JsonFeatures : public JsonHandler
{

public:
    JsonFeatures(string filename);
    ~JsonFeatures();
    string getDetectorType(const rapidjson::Value& doc);
    void setDetectorType(rapidjson::Value& doc, string newType);
    string getDescriptorType(const rapidjson::Value& doc);
    void setDescriptorType(rapidjson::Value& doc, string newType);
    string getMatcherType(const rapidjson::Value& doc);
    void setMatcherType(rapidjson::Value& doc, string newType);

private:
    vector<string> detectorTypePath;
    vector<string> descriptorTypePath;
    vector<string> matcherTypePath;
    string detectorType;
    string descriptorType;
    string matcherType;
};


// images class
class JsonImages: public JsonHandler
{

public:
    JsonImages(string filename);
    ~JsonImages();
    ImageSample getNumImage(const rapidjson::Value& doc);
    string getFilename(const rapidjson::Value& doc, int imageIdx);
    string getFolderName(const rapidjson::Value& doc, int imageIdx);
    ImageSize getImageSize(const rapidjson::Value& doc, int imageIdx);
    int getNumObject(const rapidjson::Value& doc, int imageIdx);
    vector<ImageObject> getObjectList(const rapidjson::Value& doc, int imageIdx);
    vector<int> getObjectIdList(const rapidjson::Value& doc, int imageIdx);
    ImageObject getSingleObject(const rapidjson::Value& doc, int imageIdx, int objectIdx);
    //string getObjectName(int imageIdx, int objectIdx);
    //ImageRegion getObjectRegion(int imageIdx, int objectIdx);
};

} // namespace fys

#endif // _H_JSON_HANDLER

