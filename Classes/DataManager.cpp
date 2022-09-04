#include "DataManager.h"
#include "cocos2d.h"
#include "fstream"
namespace 
{
	constexpr const char* HIGH_SCORE_TXT_PATH = "highScore.txt";
	constexpr const char* HIGH_SCORE_STR = "High Score: ";
}

//static highscore variable for managing highscore events.
int DataManager::highScore = 0;

//Write new highscore if given parameter is greater.
void DataManager::WriteHighScore(int _highScore)
{
	if (_highScore > highScore)
	{
		std::ofstream highScoreFile;
		highScoreFile.open(HIGH_SCORE_TXT_PATH);
		std::string hScoreStr = HIGH_SCORE_STR;
		hScoreStr += std::to_string(_highScore);
		highScoreFile << hScoreStr;
		highScoreFile.close();

		cocos2d::log("successfully overwrited highscore.");
	}
	else
	{
		cocos2d::log("Score is lower than highscore.");
	}
}
//Reads highscore from created highScore.txt file.
void DataManager::ReadHighScore()
{
	std::string fullText;
	std::ifstream HighScoreFile(HIGH_SCORE_TXT_PATH);

	if (HighScoreFile)
	{
		int counter = 0;
		while (getline(HighScoreFile, fullText, ':')) {
			if (counter == 1 && fullText != "")
			{
				highScore = stoi(fullText);
				break;
			}
			counter++;
		}


		HighScoreFile.close();
		cocos2d::log("High score read from file successfuly");
	}
	else
	{
		cocos2d::log("High score file not found.");
	}


}
//Return the highscore value.
int DataManager::GetHighScore()
{
	return highScore;
}
