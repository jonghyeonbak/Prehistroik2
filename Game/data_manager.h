#pragma once
#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

class DataManager
{
private:
	int		max_life;
	int		life;
	int		energy;
	int		score;

private:
	static DataManager*		m_instance;

public:
	DataManager();
	~DataManager();

public:
	void	Initialize();
	void	LateUpdate();
	void	Release();

public:
	const int& GetEnergy() const { return energy; }
	const int& GetLife() const { return life; }
	const int& GetScore() const { return score; }
public:
	void		SetEnergy(int energy_) { energy = energy_; }
	void		SetScore(int score_) { score = score_; }
	void		SetLife(int life_) { life = life_; }

public:
	void		AddEnergy(int energy_) { energy += energy_; }
	void		AddScore(int score_) { score += score_; }
	void		AddLife(int life_) { life += life_; }



public:
	static DataManager* GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new DataManager;
		}

		return m_instance;
	}

	static void DestroyInstance()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

#endif // !DATA_MANAGER_H_
