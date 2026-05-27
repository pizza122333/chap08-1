#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 입력 영상 불러오기
    Mat src = imread("tekapo.bmp");
    if (src.empty()) {
        cerr << "이미지를 불러올 수 없습니다!" << endl;
        return -1;
    }

    // 원본 영상의 가로, 세로 크기 구하기
    float w = static_cast<float>(src.cols);
    float h = static_cast<float>(src.rows);

    // 2. 힌트에 따른 원본 영상의 점 3개 지정 (좌측상단, 우측상단, 우측하단)
    Point2f src_pts[3];
    src_pts[0] = Point2f(0, 0);          // 좌측상단
    src_pts[1] = Point2f(w - 1, 0);      // 우측상단
    src_pts[2] = Point2f(w - 1, h - 1);  // 우측하단

    // 3. 2배로 늘어날 결과 영상의 점 3개 지정
    Point2f dst_pts[3];
    dst_pts[0] = Point2f(0, 0);                  // 좌측상단은 그대로 (0,0)
    dst_pts[1] = Point2f((w - 1) * 2.0f, 0);      // 우측상단 가로 2배
    dst_pts[2] = Point2f((w - 1) * 2.0f, (h - 1) * 2.0f); // 우측하단 가로, 세로 모두 2배

    // 4. 어파인 변환 행렬 M 구하기
    Mat M = getAffineTransform(src_pts, dst_pts);

    // 콘솔 창에 변환 행렬 M 출력하기 (문제 파일의 디버그 콘솔 결과 확인용)
    cout << M << endl;

    // 5. 어파인 변환 적용하기
    // 지시사항에 따라 dsize를 입력 영상의 2배 크기인 Size(src.cols * 2, src.rows * 2)로 설정합니다.
    Mat dst;
    warpAffine(src, dst, M, Size(src.cols * 2, src.rows * 2));

    // 6. 결과 화면 출력
    imshow("src", src);
    imshow("dst", dst);

    waitKey(0); // 키 입력이 있을 때까지 대기
    return 0;
}