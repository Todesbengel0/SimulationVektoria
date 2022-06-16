#pragma once

class Score
{
public:
	Score(const float& timeRegress);

	void update(const float& timeDelta);
	void increase(const float& multiplier);
	void decrease(const double& decreaseBy);

	const double& getCurrentScore() const;
	const double& getHighscore() const;
	const float& getTimeSinceIncrease() const;

private:
	double m_currentScore;
	double m_highscore;
	float m_timeSinceIncrease;
	const float m_timeRegress;
};

