#include "pch.h"
#include "Score.h"

Score::Score(const float& timeRegress)
	: m_timeRegress(timeRegress)
	, m_currentScore(0.0)
	, m_highscore(0.0)
	, m_timeSinceIncrease(0.0)
{ }

void Score::update(const float& timeDelta)
{
	m_timeSinceIncrease += timeDelta;

	if (m_currentScore == 0.0 || m_timeRegress == 0.0) return;

	m_currentScore -= m_timeRegress * timeDelta;
}

void Score::increase(const float& multiplier)
{
	m_timeSinceIncrease = 0.0f;

	m_currentScore += 100 * multiplier;

	if (m_currentScore > m_highscore)
		m_highscore = m_currentScore;
}

void Score::decrease(const double& decreaseBy)
{
	m_currentScore -= decreaseBy;

	if (m_currentScore < 0.0)
		m_currentScore = 0.0;
}

const double& Score::getCurrentScore() const
{
	return m_currentScore;
}

const double& Score::getHighscore() const
{
	return m_highscore;
}

const float& Score::getTimeSinceIncrease() const
{
	return m_timeSinceIncrease;
}
