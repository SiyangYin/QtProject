//#include "stdafx.h"
//#include <iostream>
//#include <thread>
//#include <vector>
//#include <windows.h>
////#include <opencv2/opencv.hpp>
//#include <fstream>
//#include <stdio.h>
////#include <fstream.h>
////#include <opencv2/opencv.hpp>
////using namespace cv;
//using namespace std;

///*
//int main()
//{
//    // 写文件
//    ofstream outFile;
//    outFile.open("C:\\Users\\12170\\Desktop\\Data\\data.csv", ios::out); // 打开模式可省略

//    if (outFile.is_open())
//    {
//        cout << "open success" << endl;
//        getchar();
//    }
//    if (!outFile.is_open())
//    {
//        cout << "open failed" << endl;
//        getchar();
//        exit(EXIT_FAILURE);
//    }

//    outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
//    outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
//    outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
//    outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
//    outFile.close();

//    // 读文件
//    ifstream inFile("C:\\Users\\12170\\Desktop\\Data\\data.csv", ios::in);

//    if (inFile.is_open())
//    {
//        cout << "open success" << endl;
//        getchar();
//    }
//    if (!inFile.is_open())
//    {
//        cout << "open failed" << endl;
//        getchar();
//        exit(EXIT_FAILURE);
//    }

//    string lineStr;
//    vector<vector<string>> strArray;
//    while (getline(inFile, lineStr))
//    {
//        // 打印整行字符串
//        cout << lineStr << endl;
//        // 存成二维表结构
//        stringstream ss(lineStr);
//        string str;
//        vector<string> lineArray;
//        // 按照逗号分隔
//        while (getline(ss, str, ','))
//            lineArray.push_back(str);
//        strArray.push_back(lineArray);
//    }

//    getchar();
//    return 0;
//}


//int main()
//{

//    /*char str[2000];
//    fstream file_op("c:\\Users\12170\Desktop\Data\lidar_data_2.txt", ios::in);
//    while (file_op >> str)
//        cout << str;

//    file_op.close();
//    */

	
//    /*
//    ifstream inFile;
//    inFile.open("c:\\data.csv");
//    if (inFile.is_open())
//    {
//        cout << "open success" << endl;
//        getchar();
//    }
//    if (!inFile.is_open())
//    {
//        cout << "open failed" << endl;
//        getchar();
//        exit(EXIT_FAILURE);
//    }
//    inFile.close();


//    ofstream outFile;
//    outFile.open("c:\\data.csv");
//    if (outFile.is_open())
//    {
//        cout << "open success" << endl;
//        getchar();
//    }
//    if (!outFile.is_open())
//    {
//        cout << "open failed" << endl;
//        getchar();
//        exit(EXIT_FAILURE);
//    }
//    outFile.close();

//    return 0;
//}
//*/



//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif

//#ifndef M_2PI
//#define M_2PI 6.2831853071795864769
//#endif

//#ifndef DEG2RAD
//#define DEG2RAD(x) ((x) * M_PI / 180.0)
//#endif

//#ifndef RAD2DEG
//#define RAD2DEG(x) ((x) * 180.0 / M_PI)
//#endif

//#define MAP_RESOLUTION 2
//#define MIN_DISTANCE 100
//#define MAX_DISTANCE 1000
//#define LIDAR_RESOLUTION 0.02
//#define IMAGE_SIZE (MAX_DISTANCE/MAP_RESOLUTION+10)*2
//#define DEEPTH 30.0
//#define HZ 6.0
//#define QUALITY 200

//#define FILTER_RADIUS 3

///*

////extern "C" __declspec(dllimport) bool openLiDAR(char * comName);
//extern "C" __declspec(dllimport) bool isMapReady();
//extern "C" __declspec(dllimport) int getMapData(char *buff);

//typedef struct MapDataTypeDef{
//    float angle;
//    uint16_t distance;
//    uint8_t confidence;
//};


//typedef struct LidarPoint
//{
//    MapDataTypeDef data;
//    int flag;
//    //Point2i p;
//};
//*/
///*
//typedef struct ChargerPoint
//{
//    Point2i p;
//    float phi;
//};

//typedef struct PointGroup{
//    int start, end, sum;
//    int avgdis, errdis;
//    float delt_angle;
//    float lblack_angle, rblack_angle;
//    Point2i cent;
//    Point2i lp, rp;
//    PointGroup() {
//        start = end = sum = 0;
//        avgdis = errdis = 0;
//        delt_angle = 0;
//        lblack_angle = rblack_angle = 0;
//        cent = Point2i(0, 0);
//        lp = Point2i(0, 0);
//        rp = Point2i(0, 0);
//    }
//};



//vector<Point2i> gLPs, gRPs;

//void WriteLidar(const vector<LidarPoint> &Lidar2D, string name, vector<Point2i> &vpos, vector<ChargerPoint> &vcharger)
//{
//    Mat m(IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, Scalar::all(0));

//    Point2i cent(m.cols / 2, m.rows / 2);
//    circle(m, cent, 3, Scalar(0, 0, 255), -1);
//    circle(m, cent, 1000 / MAP_RESOLUTION, Scalar(0, 255, 0));
//    circle(m, cent, 2000 / MAP_RESOLUTION, Scalar(255, 0, 0));
//    //circle(m, cent, 3000 / MAP_RESOLUTION, Scalar(0, 0, 255));
//    Point2i va(0, m.cols / 2);
//    Point2i vb(m.rows, m.cols / 2);
//    line(m, va, vb, Scalar(255, 0, 0));
//    Point2i ha(m.rows / 2, 0);
//    Point2i hb(m.rows / 2, m.cols);
//    line(m, ha, hb, Scalar(255, 0, 0));

//    for (int i = 0; i < Lidar2D.size(); i++) {
//        if (Lidar2D[i].flag) {
//            Point2i tmp = Lidar2D[i].p / MAP_RESOLUTION + cent;
//            m.at<cv::Vec3b>(m.rows - tmp.y, tmp.x)[0] = 255;
//            m.at<cv::Vec3b>(m.rows - tmp.y, tmp.x)[1] = 255;
//            m.at<cv::Vec3b>(m.rows - tmp.y, tmp.x)[2] = 255;
//            //m.at<cv::Vec3b>(tmp.y, tmp.x)[0] = 255;
//            //m.at<cv::Vec3b>(tmp.y, tmp.x)[1] = 255;
//            //m.at<cv::Vec3b>(tmp.y, tmp.x)[2] = 255;
//            //circle(m, tmp, 1, Scalar(255, 255, 255));
//        }
//    }

//    for (int i = 0; i < vpos.size(); i++) {
//        Point2i tmp = vpos[i] / MAP_RESOLUTION + cent;
//        tmp.y = m.rows - tmp.y;
//        circle(m, tmp, 5, Scalar(0, 0, 255));

//        Point2i tmpl = gLPs[i] / MAP_RESOLUTION + cent;
//        Point2i tmpr = gRPs[i] / MAP_RESOLUTION + cent;
//        tmpl.y = m.rows - tmpl.y;
//        tmpr.y = m.rows - tmpr.y;
//        line(m, tmpl, tmpr, Scalar(0, 0, 255));
//    }

//    for (int i = 0; i < vcharger.size(); i++) {
//        Point2i tp = vcharger[i].p;
//        Point2i tmp = tp / MAP_RESOLUTION + cent;
//        tmp.y = m.rows - tmp.y;
//        circle(m, tmp, 5, Scalar(0, 255, 0));
//        cout << tp << endl;

//        float tmpphi = vcharger[i].phi + 1.5*M_PI;
//        Point2i a = tp, b = tp;
//        int dx = 100 * sin(tmpphi);
//        int dy = 100 * cos(tmpphi);
//        a += Point2i(dx, dy);
//        b += Point2i(-dx, -dy);

//        Point2i tmpl = a / MAP_RESOLUTION + cent;
//        Point2i tmpr = b / MAP_RESOLUTION + cent;
//        tmpl.y = m.rows - tmpl.y;
//        tmpr.y = m.rows - tmpr.y;
//        line(m, tmpl, tmpr, Scalar(0, 255, 0));
//    }


//    static int imind = 0;
//    imind++;
//    string impath = "output/" + to_string(imind) + ".bmp";
//    imwrite(impath, m);
//    imshow(name, m);
//    if (!vpos.empty() || !vcharger.empty()) {
//        cout << "size = " << vpos.size() << " " << vcharger.size() << endl;
//        waitKey(2000);
//    }
//    waitKey(10);
//}
//void WriteLidar(const vector<LidarPoint> &Lidar2D, string name, vector<Point2i> &vpos)
//{
//    Mat m(IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, Scalar::all(0));

//    Point2i cent(m.cols / 2, m.rows / 2);
//    circle(m, cent, 3, Scalar(0, 0, 255), -1);
//    circle(m, cent, 1000 / MAP_RESOLUTION, Scalar(0, 255, 0));
//    circle(m, cent, 2000 / MAP_RESOLUTION, Scalar(255, 0, 0));
//    //circle(m, cent, 3000 / MAP_RESOLUTION, Scalar(0, 0, 255));
//    Point2i va(0, m.cols / 2);
//    Point2i vb(m.rows, m.cols / 2);
//    line(m, va, vb, Scalar(255, 0, 0));
//    Point2i ha(m.rows / 2, 0);
//    Point2i hb(m.rows / 2, m.cols);
//    line(m, ha, hb, Scalar(255, 0, 0));

//    for (int i = 0; i < Lidar2D.size(); i++) {
//        if (Lidar2D[i].flag) {
//            Point2i tmp = Lidar2D[i].p / MAP_RESOLUTION + cent;
//            m.at<cv::Vec3b>(m.rows - tmp.y, tmp.x)[0] = 255;
//            m.at<cv::Vec3b>(m.rows - tmp.y, tmp.x)[1] = 255;
//            m.at<cv::Vec3b>(m.rows - tmp.y, tmp.x)[2] = 255;
//            //m.at<cv::Vec3b>(tmp.y, tmp.x)[0] = 255;
//            //m.at<cv::Vec3b>(tmp.y, tmp.x)[1] = 255;
//            //m.at<cv::Vec3b>(tmp.y, tmp.x)[2] = 255;
//            //circle(m, tmp, 1, Scalar(255, 255, 255));
//        }
//    }

//    for (int i = 0; i < vpos.size(); i++) {
//        Point2i tmp = vpos[i] / MAP_RESOLUTION + cent;
//        tmp.y = m.rows - tmp.y;
//        circle(m, tmp, 5, Scalar(0, 0, 255));

//        Point2i tmpl = gLPs[i] / MAP_RESOLUTION + cent;
//        Point2i tmpr = gRPs[i] / MAP_RESOLUTION + cent;
//        tmpl.y = m.rows - tmpl.y;
//        tmpr.y = m.rows - tmpr.y;
//        line(m, tmpl, tmpr, Scalar(0, 0, 255));
//    }

//    imshow(name, m);
//    waitKey(10);
//}
//void PointFilter(vector<LidarPoint> &Lidar2D)
//{
//    //point noise
//    vector<int> vnb;
//    vector<int> vnw;
//    for (int i = 0; i < Lidar2D.size(); i++) {
//        int black = 0;
//        int white = 0;
//        for (int j = i - FILTER_RADIUS; j <= i + FILTER_RADIUS; j++) {
//            int ind = (j + Lidar2D.size()) % Lidar2D.size();
//            if (Lidar2D[ind].flag == 0) black++;
//            else white++;
//        }
//        if (black > FILTER_RADIUS + 1)	vnb.push_back(i);
//        if (white > FILTER_RADIUS + 1)	vnw.push_back(i);

		
//        //compensate
//        //int il = (i - 1 + Lidar2D.size()) % Lidar2D.size();
//        //int ir = (i + 1) % Lidar2D.size();
//        //if (Lidar2D[il].flag == Lidar2D[ir].flag && Lidar2D[i].flag != Lidar2D[il].flag) {
//        //	if (Lidar2D[i].flag == 0) {
//        //		Lidar2D[i].data.confidence = (Lidar2D[il].data.confidence + Lidar2D[ir].data.confidence) / 2;
//        //		Lidar2D[i].data.distance = (Lidar2D[il].data.distance + Lidar2D[ir].data.distance) / 2;
//        //		Lidar2D[i].data.angle = (Lidar2D[il].data.angle + Lidar2D[ir].data.angle) / 2;
//        //		if (Lidar2D[ir].data.angle < Lidar2D[il].data.angle) {
//        //			Lidar2D[i].data.angle += 180.0;
//        //			if (Lidar2D[i].data.angle >= 360.0) Lidar2D[i].data.angle -= 360.0;
//        //		}
//        //		Lidar2D[i].p.x = Lidar2D[i].data.distance * sin(DEG2RAD(Lidar2D[i].data.angle));
//        //		Lidar2D[i].p.y = Lidar2D[i].data.distance * cos(DEG2RAD(Lidar2D[i].data.angle));
//        //	}
//        //	Lidar2D[i].flag = 1 - Lidar2D[i].flag;
//        //}
//    }
//    for (int i = 0; i < vnb.size(); i++)	Lidar2D[vnb[i]].flag = 0;
//}
//void Revise(vector<LidarPoint> &Lidar2D, int l, int r)
//{
//    while (l < r) {
//        LidarPoint tmp = Lidar2D[l];
//        Lidar2D[l] = Lidar2D[r];
//        Lidar2D[r] = tmp;
//        l++; r--;
//    }
//}
//bool CreatPointGroup(vector<LidarPoint> &Lidar2D, vector<PointGroup> &vG)
//{
//    int i = 0;
//    while (Lidar2D[i].flag) i++;
//    Revise(Lidar2D, 0, i);
//    Revise(Lidar2D, i + 1, Lidar2D.size() - 1);
//    Revise(Lidar2D, 0, Lidar2D.size() - 1);

//    for (int i = 0; i < Lidar2D.size(); ) {
//        PointGroup tmp;
//        if (i >= Lidar2D.size()) break;
//        while (i<Lidar2D.size() && Lidar2D[i].flag == 0) i++;
//        tmp.start = i;
//        if (i >= Lidar2D.size()) break;
//        while (i < Lidar2D.size() && Lidar2D[i].flag) i++;
//        tmp.end = i - 1;
//        tmp.sum = tmp.end - tmp.start + 1;
//        if (tmp.sum < 3) continue;

//        tmp.avgdis = tmp.errdis = 0;
//        for (int j = tmp.start + 1; j <= tmp.end - 1; j++) {
//            tmp.avgdis += Lidar2D[j].data.distance;
//            tmp.cent += Lidar2D[j].p;
//        }
//        tmp.avgdis /= tmp.sum - 2;
//        tmp.cent /= tmp.sum - 2;
//        for (int j = tmp.start + 1; j <= tmp.end - 1; j++) {
//            int d = abs(Lidar2D[j].data.distance - tmp.avgdis);
//            if (d > tmp.errdis) tmp.errdis = d;
//        }
//        tmp.delt_angle = Lidar2D[tmp.end].data.angle - Lidar2D[tmp.start].data.angle+1.0;//
//        if (tmp.delt_angle < 0) tmp.delt_angle += 360.0;
//        vG.push_back(tmp);
//    }

//    for (int i = 0; i < vG.size(); i++) {
//        int il = (i - 1 + vG.size()) % vG.size();
//        int ir = (i + 1) % vG.size();
//        vG[i].lblack_angle = Lidar2D[vG[i].start].data.angle - Lidar2D[vG[il].end].data.angle;
//        vG[i].rblack_angle = Lidar2D[vG[ir].start].data.angle - Lidar2D[vG[i].end].data.angle;
//        if (vG[i].lblack_angle < 0) vG[i].lblack_angle += 360.0;
//        if (vG[i].rblack_angle < 0) vG[i].rblack_angle += 360.0;
//    }

//    return true;
//}
//bool FindCharger(vector<LidarPoint> &Lidar2D, Point2i &ChargPos, float &angle, vector<Point2i> &vpos)
//{
//    int itt;
//    for (itt = 0; itt < Lidar2D.size(); itt++)
//        if (Lidar2D[itt].flag) break;
//    if (itt >= Lidar2D.size()) return false;

//    PointFilter(Lidar2D);

//    vector<PointGroup> vG;
//    CreatPointGroup(Lidar2D, vG);

	
//    vector<PointGroup> vCG;
//    for (int i = 0; i < vG.size(); i++) {
//        int il = (i - 1 + vG.size()) % vG.size();
//        int ir = (i + 1) % vG.size();
//        Point2i lpos = Lidar2D[(vG[il].end - 1 + Lidar2D.size()) % Lidar2D.size()].p;
//        Point2i rpos = Lidar2D[(vG[ir].start + 1) % Lidar2D.size()].p;
//        Point2i cpos = (lpos + rpos) / 2;
//        int cposn = sqrt(cpos.dot(cpos));
//        Point2i dpos = vG[i].cent - cpos;
//        int dis = sqrt(dpos.dot(dpos));
//        int disres = sqrt(vG[i].avgdis * vG[i].avgdis * LIDAR_RESOLUTION * LIDAR_RESOLUTION);

//        //distance to middle point
//        //if (abs(dis - DEEPTH) < disres && vG[i].avgdis > cposn) {
//        if (dis <= 6) {
//            //cout << dis << ", " << disres << ", " << dis - disres << endl;
//            Point2f lr = rpos - lpos;
//            float lrn = sqrt(lr.ddot(lr));
//            Point2f oc = -vG[i].cent;
//            float ocn = sqrt(oc.ddot(oc));
//            float phi = acos(lr.ddot(oc) / (lrn * ocn));
//            if (phi > M_PI / 2) phi = M_PI - phi;
//            float alph = atan(25 * sin(phi) / vG[i].avgdis);
//            int np = 2 * alph / DEG2RAD(HZ/6.0);

//            //no. of points
//            //cout << np << ", " << vG[i].sum << ", " << abs(np - vG[i].sum) << endl;
//            if (abs(np - vG[i].sum) <= 2) {
//                vG[i].errdis = 0;// + 1 - 1
//                for (int j = vG[i].start; j <= vG[i].end; j++) {
//                    Point2f lc = Lidar2D[j].p - lpos;
//                    float lcn = sqrt(lc.ddot(lc));
//                    float clr = acos(min(lr.ddot(lc) / (lrn * lcn), 1.0));
//                    float e = sin(clr)*lcn;
//                    //vG[i].errdis += fabs(e - DEEPTH);
//                    vG[i].errdis += e;
//                }
//                vG[i].errdis /= vG[i].end - vG[i].start + 1;

//                //avg error of points
//                //cout << vG[i].errdis << ", " << vG[i].avgdis*LIDAR_RESOLUTION / 3 << ", "
//                //	<< vG[i].errdis - vG[i].avgdis*LIDAR_RESOLUTION / 3 << endl;
//                if (vG[i].errdis <= 1) {
//                    float min_angle = (vG[i].lblack_angle + vG[i].rblack_angle) / 2;

//                    //left right angle
//                    //cout << vG[i].delt_angle << ", " << min_angle << ", "
//                    //cout << fabs(vG[i].delt_angle - min_angle) << endl;
//                    if (fabs(vG[i].delt_angle - min_angle) < 2.0) {
						
//                        //left right group
//                        //cout << vG[il].sum << ", " << vG[ir].sum << endl;
//                        if (vG[il].sum >= 2 && vG[ir].sum >= 2) {
//                            int el, er;
//                            el = er = 0;
//                            for (int j = 1; j <= 2; j++) {
//                                int rind = vG[ir].start + j-1;
//                                vG[i].rp += Lidar2D[rind].p;

//                                Point2f lc = Lidar2D[rind].p - lpos;
//                                float lcn = sqrt(lc.ddot(lc));
//                                float clr = acos(min(lr.ddot(lc) / (lrn * lcn), 1.0));
//                                float e = sin(clr)*lcn;
//                                er += e;
//                            }
//                            vG[i].rp /= 2;
//                            er /= 2;
//                            for (int j = 1; j <= 2; j++) {
//                                int lind = vG[il].end - j + 1;
//                                vG[i].lp += Lidar2D[lind].p;

//                                Point2f rc = Lidar2D[lind].p - rpos;
//                                float rcn = sqrt(rc.ddot(rc));
//                                float crl = acos(min(-lr.ddot(rc) / (lrn * rcn), 1.0));
//                                float e = sin(crl)*rcn;
//                                el += e;
//                            }
//                            vG[i].lp /= 2;
//                            el /= 2;

//                            //avg error of points for left and right
//                            //cout << er << ", " << el << endl;//vG[i].avgdis*LIDAR_RESOLUTION/3
//                            if (er <= 1 && el <= 1) {

//                                vCG.push_back(vG[i]);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }

//    gLPs.clear();
//    gRPs.clear();
//    for (int i = 0; i < vCG.size(); i++) {
//        vpos.push_back(vCG[i].cent);
//        gLPs.push_back(vCG[i].lp);
//        gRPs.push_back(vCG[i].rp);
//    }

//    if (vCG.size() > 1) cout << vCG.size() << endl;

//    if(vCG.empty())	return false;
//    else return true;
//}
//bool cmp_angle(LidarPoint &a, LidarPoint &b)
//{
//    return a.data.angle < b.data.angle;
//}


//void testInput(int argc, char *argv[])
//{
	
//    FILE *pf;
//    pf = fopen("C:\\Users\\12170\\Desktop\\Data\\lidar_data_2.txt", "r");
//    LidarPoint tmpPoint;
//    int n = 0;

//    ofstream outFile;
//    outFile.open(argv[1]);		 //  create the file.
//    //outFile.open("C:\\Users\\12170\\Desktop\\Data\\.csv");		 //  create the file.
//    //outFile.open("C:\\Users\\12170\\Desktop\\Data\\data2.csv"); // 打开模式可省略

//    if (outFile.is_open())
//    {
//        cout << "open success" << endl;
//        getchar();
//    }
//    if (!outFile.is_open())
//    {
//        cout << "open failed" << endl;
//        getchar();
//        exit(EXIT_FAILURE);
//    }

//    while (pf)
//    {
//        cout << ++n << endl;
//        if (n > 500) break;
//        vector<LidarPoint> Lidar2D;
//        float dis;
//        int cond;

//        int countEffectivePoint = 0;		//initialize the number.

//        for (int i = 0; i < 360; i++)
//        {
//            fscanf(pf, "%f%d", &dis, &cond);
//            tmpPoint.data.distance = (uint16_t)(dis * 1000);
//            tmpPoint.data.angle = i;
//            tmpPoint.data.confidence = cond;

//            if (tmpPoint.data.distance > MAX_DISTANCE || tmpPoint.data.distance < MIN_DISTANCE)
//                tmpPoint.data.distance = 0;
//            tmpPoint.flag = tmpPoint.data.distance > 0 ? 1 : 0;
//            tmpPoint.flag = tmpPoint.data.confidence >= QUALITY ? 1 : 0;


//            if (tmpPoint.data.distance != 0) countEffectivePoint++;		//count the number of effecive point.

//            outFile << tmpPoint.data.distance << ',';


//            //tmpPoint.data.angle = (int)(tmpPoint.data.angle + 0.5);
//            tmpPoint.p.x = tmpPoint.data.distance * sin(DEG2RAD(tmpPoint.data.angle));
//            tmpPoint.p.y = tmpPoint.data.distance * cos(DEG2RAD(tmpPoint.data.angle));
//            Lidar2D.push_back(tmpPoint);
//        }

//        float effectivePointRate = ((float)countEffectivePoint) / 360;		//calculate the effective point rate.
//        outFile << effectivePointRate << "\n";		//write the effective point rate at the end of each line and change line.


//        sort(Lidar2D.begin(), Lidar2D.end(), cmp_angle);

//        vector<Point2i> vpos;
//        WriteLidar(Lidar2D, "lidar original", vpos);
//        //waitKey(100);

//        Point2i ChargPos;
//        float angle;
//        bool isFind = FindCharger(Lidar2D, ChargPos, angle, vpos);

//        vector<ChargerPoint> vcharger;
//        ChargerPoint chargetmp;
//        int ncharger;
//        fscanf(pf, "%d", &ncharger);
//        for (size_t i = 0; i < ncharger; i++)
//        {
//            float x, y, phi, disCode;
//            fscanf(pf, "%f%f%f", &x, &y, &phi);
//            fscanf(pf, "%f", &disCode);
//            cout << "disCode = " << disCode << ", ";
//            chargetmp.p.x = (int)(y * 1000);
//            chargetmp.p.y = (int)(x * 1000);
//            chargetmp.phi = phi;
//            vcharger.push_back(chargetmp);
//        }

//        if (isFind) {
//            cout << "bad lidar" << n << endl;
//            continue;
//        }

//        WriteLidar(Lidar2D, "lidar", vpos, vcharger);
//        waitKey(100);
//    }


//    outFile.close();

//    fclose(pf);

	
//}

//void fun()
//{
//    string Degree[5] = { "博硕","本科","专科" };		//16*2	16*1  16*0
//    string Study[5] = { "是","否" };					//8*1	8*0
//    string School[5] = { "211","非211" };			//4*1	4*0
//    string Year[5] = { "0-2","3-5","6-10" ,"10-" };	//3		2		1   0
//    for (int iD = 0; iD < 3; iD++) //{
//        cout << Degree[iD] << "\t" << iD * 16 << endl;
//        for (int iS = 0; iS < 2; iS++) //{
//            cout << Study[iS] << "\t" << iS * 8 << endl;
//            for (int iSS = 0; iSS < 2; iSS++) //{
//                cout << School[iSS] << "\t" << iSS * 4 << endl;
//                for (int iY = 0; iY < 4; iY++)//{
//                    cout << Year[iY] << "\t" << iY * 1 << endl;
//                    //cout << "no." << iD * 16 + iS * 8 + iSS * 4 + iY + 1 << " ";
//                    //cout << Degree[iD] << " " << Study[iS] << " " << School[iSS] << " " << Year[iY] << endl;
//    //			}
//    //		}
//    //	}
//    //}

//    getchar();
//}

//*/

////int main(int argc, char *argv[])
////int main()

//int MainWindow::lidar()
//{
//    //fun();
//    //testInput(argc, argv);
	
//    getchar();

//    unsigned long long PointLen = sizeof(MapDataTypeDef);
//    char *p = new char[PointLen * 3000];
//    MapDataTypeDef map;
//    LidarPoint tmpPoint;

//    ofstream outFile;
//    //outFile.open(argv[1]);		 //  create the file.
//    outFile.open("C:\\Users\\12170\\Desktop\\Data\\data5.csv");		 //  create the file.

//    if (openLiDAR("COM3"))
//    {
//        int frameAmount = 0;		//initialize the frameAmount
//        while (++frameAmount <= 500)		//count the frameAmount
//        {
//            if (isMapReady())
//            {
//                vector<LidarPoint> Lidar2D;

//                int len = getMapData(p)/PointLen -1;
//                char *pt = p;

//                int countEffectivePoint = 0;		//initialize the number.

//                //for (int i = 0; i < len; i++) {
//                for (int i = 0; i < 360; i++) {
//                    tmpPoint.data = *(MapDataTypeDef*)pt;
//                    if (tmpPoint.data.distance > MAX_DISTANCE || tmpPoint.data.distance < MIN_DISTANCE)
//                        tmpPoint.data.distance = 0;
//                    tmpPoint.flag = tmpPoint.data.distance > 0 ? 1 : 0;
//                    tmpPoint.flag = tmpPoint.data.confidence > QUALITY ? 1 : 0;

//                    if (tmpPoint.data.distance != 0) countEffectivePoint++;		//count the number of effecive point.

//                    outFile << tmpPoint.data.distance << ',';		//write distance data, comma break.

//                    //tmpPoint.data.angle = (int)(tmpPoint.data.angle + 0.5);
//                    //tmpPoint.p.x = tmpPoint.data.distance * sin(DEG2RAD(tmpPoint.data.angle));
//                    //tmpPoint.p.y = tmpPoint.data.distance * cos(DEG2RAD(tmpPoint.data.angle));
//                    Lidar2D.push_back(tmpPoint);
//                    pt += PointLen;
//                }

//                float effectivePointRate = ((float)countEffectivePoint) / len;		//calculate the effective point rate.
//                outFile << effectivePointRate <<"\n";		//write the effective point rate at the end of each line and change line.


//                sort(Lidar2D.begin(), Lidar2D.end(), cmp_angle);

//                vector<Point2i> vpos;
//                WriteLidar(Lidar2D, "lidar original", vpos);
				
//                Point2i ChargPos;
//                float angle;
//                FindCharger(Lidar2D, ChargPos, angle, vpos);
				
//                WriteLidar(Lidar2D, "lidar", vpos);
//                waitKey(100);


//            }
//        }
//    }

//    outFile.close();		//close the file.

//    delete p;

//    getchar();

//    return 0;
//}

