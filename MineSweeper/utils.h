#pragma once
#include "structs.h"
#include <vector>

namespace utils
{

	const float g_Pi{ 3.1415926535f };

#pragma region OpenGLDrawFunctionality
	void ClearBackground(const Color4f& color);
	void ClearBackground(float r, float g, float b);
	void ClearBackground();
	// Choose a floating point value for each color component between 0.0f and 1.0f. The a (alpha) is optional.
	// Usage: SetColor(1.0f, 0.0f, 0.0f); set the drawing color to red
	void SetColor(float r, float g, float b, float a = 1);
	// Pass a Color4f object to the function
	void SetColor(const Color4f& color);

	// Draws a line by connecting the two points specified by (x1,y1) and (x2,y2)
	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
	// Draws a line by connecting the two points specified by p1 and p1
	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth = 1.0f);

	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth = 1);
	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3);
	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rectf& rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const Point2f& bottomLeft, float width, float height);
	void FillRect(const Rectf& rect);

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Ellipsef& ellipse, float lineWidth = 1.0f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const Ellipsef& ellipse);
	void FillEllipse(const Point2f& center, float radX, float radY);

	// Draws an arc. The angle parameters are in radians, not in degrees.
	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// Draws an arc. The angle parameters are in radians, not in degrees.
	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// Fills an arc. The angle parameters are in radians, not in degrees.
	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
	// Fills an arc. The angle parameters are in radians, not in degrees.
	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle);

	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed = true, float lineWidth = 1.0f);
	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed = true, float lineWidth = 1.0f);
	void FillPolygon(const std::vector<Point2f>& vertices);
	void FillPolygon(const Point2f* pVertices, size_t nrVertices);
#pragma endregion OpenGLDrawFunctionality

#pragma region TextureFunctionality

	struct Texture
	{
		GLuint id;
		float width;
		float height;
	};
	bool TextureFromFile(const std::string& path, Texture& texture);
	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor, Texture& texture);
	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture);
	void TextureFromSurface(const SDL_Surface* pSurface, Texture& textureData);
	void DrawTexture(const Texture& texture, const Point2f& dstBottomLeft, const Rectf& srcRect = {});
	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect = {});
	void DeleteTexture(Texture& texture);
#pragma endregion TextureFunctionality

#pragma region CollisionFunctionality
	float GetDistance(const Point2f& pOne, const Point2f& pTwo);
	float GetDistance(const float XOne, const float YOne, const float XTwo, const float YTwo);
	bool IsPointInCircle(const Point2f& point, const Circlef& circle);
	bool IsPointInRect(const Point2f& point, const Rectf& rectangle);
	bool IsOverlapping(const Rectf& rectangleOne, const Rectf& rectangleTwo);
	bool IsOverlapping(const Circlef& circleOne, const Circlef& circleTwo);
#pragma endregion CollisionFunctionality

#pragma region VectorFuntionality
	bool GetVecEqual(const Vector2f& vec1, const Vector2f& vec2);
	float GetRadians(const float degree);
	float GetDegrees(const float randian);
	float GetAngle(const Vector2f& vec1, const Vector2f& vec2);
	float GetAngle(const Vector2f& vec);
	float GetDotProduct(const Vector2f& vec1, const Vector2f& vec2);
	float GetCrossProduct(const Vector2f& vec1, const Vector2f& vec2);
	float GetVectorLenght(const Vector2f& vec);
	std::string	VecToString(const Vector2f& vec);
	Vector2f ScaleVector(const Vector2f& vec, const float scalar);
	Vector2f NormalizeVector(const Vector2f& vec);
	Vector2f AddVectors(const Vector2f& vec1, const Vector2f& vec2);
	Point2f AddVectors(const Point2f& point, const Vector2f& vec);
	Vector2f SubtractVectors(const Vector2f& vec1, const Vector2f& vec2);
	Point2f SubtractVectors(const Point2f& point, const Vector2f& vec);
	void DrawVector(const Vector2f& vec, const Point2f& startPos = Point2f{ 0.f, 0.f });
#pragma endregion VectorFuntionality

#pragma region ArrayFuntionality
	void PrintArray(int* pNumbers, int size);
	void PrintArray(int* pNumbers, int startIdx, int endIdx);
	int GetArrayIndex(int rowIdx, int colIdx, int nrCols);
	int CountArrValue(const int* arr, const int arrSize, const int searchValue);
	int MinArrElement(const int* arr, const int arrSize);
	int MaxArrElement(const int* arr, const int arrSize);
	void SwapInArr(int* arr, const int idx1, const int idx2);
	void SwapInArr(float* arr, const int idx1, const int idx2);
	void SwapInArr(Point2f* arr, const int idx1, const int idx2);
	void SwapInArr(Texture* arr, const int idx1, const int idx2);
	void ShuffleArr(int* arr, const int arrSize, const int shuffleTimes);
	void ShuffleArr(float* arr, const int arrSize, const int shuffleTimes);
	void ShuffleArr(Point2f* arr, const int arrSize, const int shuffleTimes);
	void ShuffleArr(Texture* arr, const int arrSize, const int shuffleTimes);
	void BubbleSort(int* arr, const int arrSize);
#pragma endregion ArrayFuntionality
}