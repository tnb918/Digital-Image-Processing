#include "funtions.h"

VideoCapture createInput(bool useCamera, std::string videoPath)
{
	//选择输入
	VideoCapture capVideo;
	if (useCamera) {
		capVideo.open(0);
	}
	else {
		capVideo.open(videoPath);
	}
	return capVideo;
}

void segColor()
{
	Mat src = imread("..\\testImages\\movie.jpg");

	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey(0);

}

int kMeansDemo()
{
	//限定类别最大为5，生成5种颜色
	const int MAX_CLUSTERS = 5;
	Scalar colorTab[] =
	{
		Scalar(0, 0, 255),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};

	//生成二维特征空间
	Mat img(500, 500, CV_8UC3);
	//随机数生成类
	RNG rng(12345);

	for (;;)
	{
		//随机生成类和样本的数量
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
		int i, sampleCount = rng.uniform(1, 1001);
		//保存所有样本坐标的容器
		Mat points(sampleCount, 1, CV_32FC2), labels;

		clusterCount = MIN(clusterCount, sampleCount);
		std::vector<Point2f> centers;

		/* generate random sample from multigaussian distribution */
		for (k = 0; k < clusterCount; k++)
		{
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			Mat pointChunk = points.rowRange(k * sampleCount / clusterCount,
				k == clusterCount - 1 ? sampleCount :
				(k + 1) * sampleCount / clusterCount);
			//对矩阵填充随机数
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols * 0.05, img.rows * 0.05));
		}

		randShuffle(points, 1, &rng);

		double compactness = kmeans(points, clusterCount, labels,
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		img = Scalar::all(0);

		for (i = 0; i < sampleCount; i++)
		{
			int clusterIdx = labels.at<int>(i);
			Point ipt = points.at<Point2f>(i);
			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
		}
		for (i = 0; i < (int)centers.size(); ++i)
		{
			Point2f c = centers[i];
			circle(img, c, 40, colorTab[i], 1, LINE_AA);
		}
		cout << "Compactness: " << compactness << endl;

		imshow("clusters", img);

		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}

	return 0;
}

int createMaskByKmeans(cv::Mat src, cv::Mat& mask)
{
	if ((mask.type() != CV_8UC1)
		|| (src.size() != mask.size())
		) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;

	//制作kmeans用的数据
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//执行kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//制作mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
		}
	}

	return 0;
}

void addEffect()
{
	VideoCapture cap1;
	cap1.open("..\\testImages\\bg.mp4");
	VideoCapture cap2;
	cap2.open("..\\testImages\\dragon.mp4");
	VideoWriter video("test.avi", CV_FOURCC('M', 'P', '4', '2'), 20.0, Size(320, 568));

	int currentFrame1 = 0;
	int currentFrame2 = 0;

	while (1)
	{
		Mat frame1, frame2, frame3;

		cap1 >> frame1;
		cap2 >> frame2;

		//利用K-means抠图，制作mask
		Mat mask = Mat::zeros(frame2.size(), CV_8UC1);
		createMaskByKmeans(frame2, mask);
		frame2.copyTo(frame3, mask);
		//imshow("dragon_mask", mask);
		//imshow("dragon_after_mask", frame3);

		//不加这个判断条件视频结束后会报错
		if (!frame1.empty())
		{
			resize(frame1, frame1, frame2.size());
			frame3.copyTo(frame1,mask);
			//imshow("bg", frame1);
			//将图片转成视频并保存
			video << frame1;
		}
		
		//由于视频时长原因，对"bg.mp4"进行循环播放
		if (currentFrame1 == cap1.get(CV_CAP_PROP_FRAME_COUNT) - 1)
		{
			currentFrame1 = 0;
			cap1.set(CV_CAP_PROP_POS_FRAMES, 0);
		}

		//结束帧
		if (currentFrame2 > 440)
		{
			currentFrame2 = 0;
			cout << "Video production completed !" << endl;
			break;
		}

		waitKey(30);
		currentFrame1++;
		currentFrame2++;

	}
}