#include <stdio.h>
#include <math.h>
#define PI (3.141592653589793)

float degreeToRad(float degree){
    return degree * PI / 180; //convert degree to radians

}

void gpsToNed(float lat1, float long1, float alt1, float lat2, float long2, float alt2){
    //1's are origin, 2's are current
    float originLat = degreeToRad(lat1);    //define Origin and current latitude and longitudes
    float originLong = degreeToRad(long1);
    float currentLat = degreeToRad(lat2);
    float currentLong = degreeToRad(long2);
    float projectedLat = originLat;
    float projectedLong = originLong;

    int earthRadius = 6371000; //define Earth Radius in m

    //first we calculate longitude distance by assuming origin and current have the same latitude
    float diffLat = 0;      //calc difference in radians between two latitudes and longitudes
    float diffLong = (currentLong-originLong);

    float a = sin(diffLat/2) * sin(diffLat/2) + sin(diffLong/2) * sin(diffLong/2) * cos(originLat) * cos(projectedLat); //Haversine Formula
    float x = earthRadius * (2 * atan2(sqrt(a), sqrt(1-a)));

    //next we calculate latitude distance by assuming origin and current have same longitude
    diffLat = (currentLat-originLat);
    diffLong = 0;
    a = sin(diffLat/2) * sin(diffLat/2) + sin(diffLong/2) * sin(diffLong/2) * cos(originLat) * cos(currentLat); //Haversine Formula
    float y = earthRadius * (2 * atan2(sqrt(a), sqrt(1-a)));

    //As the Earth is flat and not a donut altitude corresponds directly to y coordinates (Negative because of NED)
    float z = -(alt2-alt1);

    // return stuff; might want to change void funtion to something useful
    printf("X distance to origin = %f", x);
    printf("Y distance to origin = %f", y);
    printf("Z distance to origin = %f", z);
}

void main() {
    float hyendLatitude = 48.751033011022784;
    float hyendLongitude = 9.101445360510834;
    float hyendAltitude = 69;
    float MensaLatitude = 48.746369733528;
    float MensaLongitude = 9.103684133496255;
    float MensaAltitude = 420;

    gpsToNed(hyendLatitude, hyendLongitude, hyendAltitude, MensaLatitude, MensaLongitude, MensaAltitude);
}