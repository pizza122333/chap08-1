#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 입력 영상 불러오기 (이미지 경로는 본인 환경에 맞게 수정하세요)
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

    // 3. 1/2로 줄어들 결과 영상의 점 3개 지정
    Point2f dst_pts[3];
    dst_pts[0] = Point2f(0, 0);                  // 좌측상단은 그대로 (0,0)
    dst_pts[1] = Point2f((w - 1) / 2.0f, 0);      // 우측상단 가로만 절반
    dst_pts[2] = Point2f((w - 1) / 2.0f, (h - 1) / 2.0f); // 우측하단 가로, 세로 모두 절반

    // 4. 어파인 변환 행렬 M 구하기
    Mat M = getAffineTransform(src_pts, dst_pts);

    // 콘솔 창에 변환 행렬 M 출력하기 (문제 파일의 디버그 콘솔 결과 확인용)
    cout << M << endl;

    // 5. 어파인 변환 적용하기
    // 결과 영상의 크기는 문제 그림처럼 검은 여백이 남도록 원본 크기(src.size())를 그대로 유지합니다.
    Mat dst;
    warpAffine(src, dst, M, src.size());

    // --- 실습과제 2 추가 영역 ---

    // 1. 원본 영상의 정중앙점 구하기
    Point2f center_pt(src.cols / 2.0f, src.rows / 2.0f);

    // 2. transform 함수에 넣기 위해 벡터(vector)에 점을 담기
    vector<Point2f> src_pts_vec;
    src_pts_vec.push_back(center_pt);

    // 3. 변환된 좌표가 저장될 결과 벡터 생성
    vector<Point2f> dst_pts_vec;

    // 4. transform 함수를 이용하여 중앙점이 어떻게 변환되었는지 계산
    // 인자: (원본 좌표벡터, 결과 좌표벡터, 어파인 변환 행렬 M)
    transform(src_pts_vec, dst_pts_vec, M);

    // 5. 계산된 좌표 콘솔창에 출력하기
    // dst_pts_vec[0]에 결과 좌표가 담겨 있습니다.
    cout << "원본 영상의 정중앙점: " << center_pt << endl;
    cout << "결과 영상에서의 중앙점 좌표: " << dst_pts_vec[0] << endl;

    // 6. 결과 화면 출력
    imshow("src", src);
    imshow("dst", dst);

    waitKey(0); // 키 입력이 있을 때까지 대기
    return 0;
}