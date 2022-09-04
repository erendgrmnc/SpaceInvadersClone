#pragma once
//Data Manager Class Definition. Managing the data-base operations like high-score recording.
class DataManager 
{
public:
	static void WriteHighScore(int _highScore);
	static void ReadHighScore();
	static int GetHighScore();
private:
	static int highScore;
};