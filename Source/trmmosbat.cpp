#include "trmmosbat.h"

trmMosbat *create_from_point(CvSeq *points,double previous)
{
    trmMosbat *obj = new trmMosbat;
    int ID = 0;
    obj->middle.x = 0;
    obj->middle.y = 0;
    obj->center1.x = 9999;
    obj->center1.y = 9999;
    obj->center2.x = 9999;
    obj->center2.y = 9999;
    obj->center3.x = 9999;
    obj->center3.y = 9999;
    obj->center4.x = 9999;
    obj->center4.y = 9999;
	
    //find centers
    for( int i=0; i < points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        obj->middle.x += p->x;
        obj->middle.y +=+ p->y;
    }
    obj->middle.x /= points->total;
    obj->middle.y /= points->total;
    for( int i=0; i < 4; i++ )
    {
        ID = 0;
        CvPoint *temp = (CvPoint*)cvGetSeqElem ( points, 0 );
        CvPoint *p;
        for( int j=1; j < points->total; j++ )
        {
            p = (CvPoint*)cvGetSeqElem ( points, j );
            if ( obj->dist_cv(obj->middle,*p) < obj->dist_cv(obj->middle,*temp) )
            {
                temp = p;
                ID = j;
            }
        }
        if ( temp->y <= obj->middle.y )
        {
            if (obj->center1.x == 9999)
            {
                obj->center1 = *temp;
            }
            else if (obj->center2.x == 9999)
            {
                obj->center2 = *temp;
            }
            else
            {
                obj->center3 = *temp;
            }
        }
        else
        {
            if (obj->center3.x == 9999)
            {
                obj->center3 = *temp;
            }
            else
            {
                obj->center4 = *temp;
            }
        }
        cvSeqRemove(points,ID);
    }

    if (obj->center1.x > obj->center2.x)
    {
        CvPoint temp = obj->center2;
        obj->center2 = obj->center1;
        obj->center1 = temp;
    }
    if (obj->center3.x < obj->center4.x)
    {
        CvPoint temp = obj->center3;
        obj->center3 = obj->center4;
        obj->center4 = temp;
    }

    obj->top1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if ((p->y) < (obj->top1.y))
        {
            obj->top1 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);
    obj->top2 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if (obj->dist_cv(obj->top1,*p) < obj->dist_cv(obj->top1,obj->top2))
        {
            obj->top2 =  *p;
            ID = i;
        }
    }

    if (obj->top1.x > obj->top2.x)
    {
        CvPoint temp = obj->top2;
        obj->top2 = obj->top1;
        obj->top1 = temp;
    }

    cvSeqRemove(points,ID);

    obj->left1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if ((p->x) < (obj->left1.x))
        {
            obj->left1 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);
    obj->left2 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if (obj->dist_cv(obj->left1,*p) < obj->dist_cv(obj->left1,obj->left2))
        {
            obj->left2 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);

    if (obj->left1.y > obj->left2.y)
    {
        CvPoint temp = obj->left2;
        obj->left2 = obj->left1;
        obj->left1 = temp;
    }

    obj->down1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if ((p->y) > (obj->down1.y))
        {
            obj->down1 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);
    obj->down2 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    ID = 0;
    for( int i=0; i<points->total; i++ )
    {
        CvPoint *p = (CvPoint*)cvGetSeqElem ( points, i );
        if (obj->dist_cv(obj->down1,*p) < obj->dist_cv(obj->down1,obj->down2))
        {
            obj->down2 =  *p;
            ID = i;
        }
    }
    cvSeqRemove(points,ID);

    if (obj->down1.x > obj->down2.x)
    {
        CvPoint temp = obj->down2;
        obj->down2 = obj->down1;
        obj->down1 = temp;
    }

    obj->right1 = *(CvPoint*)cvGetSeqElem ( points, 0 );
    obj->right2 = *(CvPoint*)cvGetSeqElem ( points, 1 );

    if (obj->right1.y > obj->right2.y)
    {
        CvPoint temp = obj->right2;
        obj->right2 = obj->right1;
        obj->right1 = temp;
    }

    obj->pr = previous;
    obj->rect = (CvPoint *)malloc( 4 * sizeof (CvPoint));
    obj->edge = (obj->dist_cv(obj->top2,obj->center2) + obj->dist_cv(obj->right1,obj->center2) + obj->dist_cv(obj->right2,obj->center3) +
                 obj->dist_cv(obj->down2,obj->center3) + obj->dist_cv(obj->down1,obj->center4) + obj->dist_cv(obj->left2,obj->center4)
                 + obj->dist_cv(obj->left1,obj->center1))/7.0;

    obj->rect[0] = cvPoint(0,0);
    obj->rect[1] = cvPoint(0,0);
    obj->rect[2] = cvPoint(0,0);
    obj->rect[3] = cvPoint(0,0);

    if ( obj->center1.x == 9999 || obj->center1.y == 9999 || obj->center2.x == 9999 || obj->center2.y == 9999 ||
         obj->center3.x == 9999 || obj->center3.y == 9999 || obj->center4.x == 9999 || obj->center4.y == 9999)
    {
        return NULL;
    }
    return obj;
}

trmMosbat::trmMosbat()
{

}

double trmMosbat::findAngle()
{
    double gradiant1 = findDerivative(top1,down1,center1,center4,true);
    gradiant1 += findDerivative(left1,right1,center1,center2);
    gradiant1 += findDerivative(left2,right2,center3,center4);
    gradiant1 += findDerivative(top2,down2,center2,center3,true);
    gradiant1 /= 4.0;
//    std::cout << findDerivative(top1,down1,center1,center4,true) << " \t " << findDerivative(left1,right1,center1,center2) <<
//                 " \t "<< findDerivative(left2,right2,center3,center4) << " \t " << findDerivative(top2,down2,center2,center3,true) << std::endl;

    return (90 + (atan(gradiant1) * 180 / PI));
}


double trmMosbat::dist_cv(CvPoint pt1, CvPoint pt2)
{
    return cv::sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x)  + (pt1.y - pt2.y) *  (pt1.y - pt2.y));
}

CvPoint* trmMosbat::getRect()
{
    double angle = findAngle();

    double m = tan((angle + 45)/180.0 * PI);
    rect[0] = center1;
    double b = -rect[0].y - m*rect[0].x;
    double d = b + rect[0].y;
    double b1 = rect[0].x - m * d;
    double a1 = (m * m + 1);
    double c1 = ( rect[0].x * rect[0].x  + d * d - 3 * edge * edge);
    double x = (b1 - cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[0].x = x;rect[0].y = - (m * x + b);

    m = tan((angle - 45)/180.0 * PI);
    rect[1] = center2;
    b = -rect[1].y - m*rect[1].x;
    d = b + rect[1].y;
    b1 = rect[1].x - m * d;
    a1 = (m * m + 1);
    c1 = ( rect[1].x * rect[1].x  + d * d - 3 * edge * edge);
    x = (b1 + cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[1].x = x;rect[1].y = - (m * x + b);


    m = tan((angle + 45)/180.0 * PI);
    rect[2] = center3;
    b = -rect[2].y - m*rect[2].x;
    d = b + rect[2].y;
    b1 = rect[2].x - m * d;
    a1 = (m * m + 1);
    c1 = ( rect[2].x * rect[2].x  + d * d - 3 * edge * edge);
    x = (b1 + cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[2].x = x;rect[2].y = - (m * x + b);

    m = tan((angle - 45)/180.0 * PI);
    rect[3] = center4;
    b = -rect[3].y - m*rect[3].x;
    d = b + rect[3].y;
    b1 = rect[3].x - m * d;
    a1 = (m * m + 1);
    c1 = ( rect[3].x * rect[3].x  + d * d - 3 * edge * edge);
    x = (b1 - cv::sqrt(b1 * b1 - a1 * c1 ))/ a1;
    rect[3].x = x;rect[3].y = - (m * x + b);

    return rect;
}


CvRect trmMosbat::trmMosbat::getRegion()
{
    getRect();
    CvRect return_data = cvRect(rect[0].x,rect[0].y,rect[0].x,rect[0].y);
    for( int i = 1; i < 4; i++ )
    {
        if ( rect[i].x < return_data.x )
            return_data.x = rect[i].x;
        if ( rect[i].y < return_data.y)
            return_data.y = rect[i].y;
        if ( rect[i].x > return_data.width )
            return_data.width = rect[i].x;
        if ( rect[i].y > return_data.height)
            return_data.height = rect[i].y;
    }

    return_data.width = return_data.width - return_data.x;
    return_data.height = return_data.height - return_data.y;

    return return_data;

}

double trmMosbat::findDerivative(CvPoint pt1, CvPoint pt2, CvPoint pt3, CvPoint pt4,bool reverse)
{
    long a1 = 4;
    long a2 = pt1.x + pt2.x + pt3.x + pt4.x;
    long b1 = a2;
    long b2 = pt1.x * pt1.x + pt2.x * pt2.x + pt3.x * pt3.x + pt4.x * pt4.x;
    long c1 = -(pt1.y + pt2.y + pt3.y + pt4.y);
    long c2 = -(pt1.x * pt1.y + pt2.x * pt2.y + pt3.x * pt3.y + pt4.x * pt4.y);

    if (reverse)
    {
        a1 = 4;
        a2 = -(pt1.y + pt2.y + pt3.y + pt4.y);
        b1 = a2;
        b2 = pt1.y * pt1.y + pt2.y * pt2.y + pt3.y * pt3.y + pt4.y * pt4.y;
        c1 = -(pt1.x + pt2.x + pt3.x + pt4.x);
        c2 = (pt1.x * pt1.y + pt2.x * pt2.y + pt3.x * pt3.y + pt4.x * pt4.y);
    }

    double mat_1 = (a1 * c2 - a2 * c1);
    double mat_2 = (a1 * b2 - a2 * b1);

    double slope = mat_1 / mat_2;

    return slope;
}

trmParam trmMosbat::Loadparam(char *filename)
{
    trmParam return_data;
    QFile json_file(filename);
    if(json_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Json::Value json_obj;
        Json::Reader reader;
        if (reader.parse(QString(json_file.readAll()).toUtf8().data(), json_obj))
        {
            return_data.bold = json_obj.get("Bold",1).asInt();
            return_data.erode = json_obj.get("Erode",1).asInt();
            return_data.dilate = json_obj.get("Dilate",1).asInt();
            return_data.calibre_width = json_obj.get("Calibre Image Width",calib_prev_size).asInt();
            return_data.frame_num = json_obj.get("Start Frame Number",0).asInt();
            return_data.isVideo = json_obj.get("Is Video",false).asBool();
            std::string buffer = json_obj.get("File Address","../Resources/Test.jpg").asString();
            int len = strlen(buffer.c_str());
            char *buffer2 = (char *)malloc(len);
            strncpy(buffer2, buffer.c_str(), len);
            return_data.filename = buffer2;

            const Json::Value edge = json_obj["Edge Detection"];
            if (!edge.empty())
            {
                return_data.edge_1 = edge.get("Treshold 1",99).asDouble();
                return_data.edge_2 = edge.get("Treshold 2",33).asDouble();
            }
            return_data.corner_min = json_obj.get("Corner Minimum Distance",0).asInt();
        }

    }
    else
    {
        return_data.bold = 1;
        return_data.erode = 12;
        return_data.dilate = 12;
        return_data.edge_1 = 383;
        return_data.edge_2 = 127;
        return_data.corner_min = 11;
        return_data.filename = "../Resources/Test.jpg";
        return_data.isVideo = false;
        return_data.frame_num = 0;
        return_data.calibre_width = calib_prev_size;
    }
    return return_data;
}

void trmMosbat::Saveparam(trmParam data,char *filename)
{
    Json::Value json_main;
    Json::Value edge;
    edge["Treshold 1"] = data.edge_1;
    edge["Treshold 2"] = data.edge_2;
    json_main["Erode"] = data.erode;
    json_main["Dilate"] = data.dilate;
    json_main["Bold"] = data.bold;
    json_main["Corner Minimum Distance"] = data.corner_min;
    json_main["File Address"] = data.filename.toUtf8().data();
    json_main["Start Frame Number"] = data.frame_num;
    json_main["Edge Detection"] = edge;
    json_main["Is Video"] = data.isVideo;
    json_main["Calibre Image Width"] = data.calibre_width;

    // write in a nice readible way
    Json::StyledWriter styledWriter;
    std::string str = styledWriter.write(json_main);
    std::vector<char> json_data(str.begin(), str.end());
    json_data.push_back('\0');
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(json_data.data());
    file.close();
}

trmMosbat *mosbatFromImage(IplImage *imagesrc,trmParam filterParam)
{
    IplImage *imgclone = cvCreateImage( cvGetSize(imagesrc), 8, 1 );
    cvCvtColor( imagesrc, imgclone, CV_BGR2GRAY );
    if (filterParam.erode)
        cvErode( imgclone, imgclone , NULL , filterParam.erode );
    if (filterParam.dilate)
        cvDilate( imgclone, imgclone , NULL , filterParam.dilate );
    IplImage *buffer = imgclone;
    imgclone = trmMosbat::doCanny( imgclone, filterParam.edge_1 ,filterParam.edge_2, 3 );
    cvReleaseImage( &buffer );
    if (filterParam.bold)
        trmMosbat::bold_filter(imgclone,filterParam.bold);
    CvSeq* firstContour = NULL;
    CvMemStorage* cnt_storage = cvCreateMemStorage();
    cvFindContours(imgclone,cnt_storage,&firstContour,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
    cvReleaseImage( &imgclone );
    CvMemStorage* poly_storage = cvCreateMemStorage();
    CvSeq *dummy_seq = firstContour;
    CvSeq *poly = NULL;
    trmMosbat *plus_mark = NULL;
    IplImage *imgout = cvCloneImage(imagesrc);
    while( dummy_seq != NULL )
    {
        poly = cvApproxPoly(dummy_seq,sizeof(CvContour),poly_storage, CV_POLY_APPROX_DP,filterParam.corner_min);
        if (poly->total == 12)
        {
            plus_mark = create_from_point(poly,0);
            //crop
            if (plus_mark != NULL)
            {
                cvSetImageROI(imgout, plus_mark->getRegion());
                IplImage *buffer = cvCreateImage(cvGetSize(imgout), imgout->depth, imgout->nChannels);
                cvCopy(imgout, buffer, NULL);
                cvResetImageROI(imgout);
                imgout = cvCloneImage(buffer);

                cvReleaseImage( &buffer );
                break;
            }
        }
        dummy_seq = dummy_seq->h_next;
    }
    cvClearMemStorage(poly_storage);
    cvReleaseMemStorage(&poly_storage);
    cvClearMemStorage(cnt_storage);
    cvReleaseMemStorage(&cnt_storage);
    cvReleaseImage( &imgout );
    return plus_mark;
}


IplImage* trmMosbat::doCanny( IplImage* in, double lowThresh, double highThresh, double aperture )
{
    if(in->nChannels != 1)
    {
        printf("Not supported\n");
        exit(0); //Canny only handles gray scale images
    }
    IplImage *out = cvCreateImage( cvGetSize( in ) , IPL_DEPTH_8U, 1 );
    cvCanny( in, out, lowThresh, highThresh, aperture );
    return( out );
}

void trmMosbat::bold_filter(IplImage *in,int kernel_size)
{
    cv::Mat grayFrame = cv::Mat(in);
    unsigned char imgdata[grayFrame.cols][grayFrame.rows];
    for (int y = 0 ; y < grayFrame.rows ; y++)
    {
        const unsigned char* ptr = (unsigned char*)(grayFrame.data + y * grayFrame.step);
        for (int x = 0 ; x < grayFrame.cols ; x++ )
        {
            imgdata[x][y] = *ptr;
            ptr++;
        }
    }
    for (int x = 0 ; x < grayFrame.cols - kernel_size ; x++)
    {
        for (int y = 0 ; y < grayFrame.rows - kernel_size ; y++ )
        {
            if (imgdata[x+kernel_size/2][y+kernel_size/2] == 255 )
            {
                cvRectangle(in,cvPoint(x,y),cvPoint(x+kernel_size,y+kernel_size),cvScalarAll(255));

            }
        }
    }
}
