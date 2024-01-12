#pragma once

#include <chrono>;
#include <thread>;
#include <atomic>;
#include <functional>;
#include<mutex>

using Thread = std::thread;
using AtomicBool = std::atomic<bool>;
using ConditionVariable = std::condition_variable;
using Mutex = std::mutex;
using TimerCallback = std::function<void()>;


class __declspec(dllexport) Timer {
public:
	//Constructors
	Timer(int total_minutes);
	//Constructor for testing
	Timer(int total_seconds, bool);
	//Destructor
	~Timer();

	//Getters
	std::chrono::milliseconds GetRemainingTime();

	//Setters
	void SetTimerResolution(int ms);
	void SetUpdateWordCallback(TimerCallback updateWordCallback);

	bool IsTimeExpired();

	//Flow of the timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();

	

private:
	void Run();

private:
	bool m_suspended;

	Thread m_thread;

	Mutex m_mutex;

	AtomicBool m_running;

	ConditionVariable m_cv;

	std::chrono::milliseconds m_initialTime;
	std::chrono::milliseconds m_remainingTime;
	std::chrono::milliseconds m_toDecreaseTime;
	std::chrono::milliseconds m_timerResolution;

	TimerCallback m_updateWord;


};