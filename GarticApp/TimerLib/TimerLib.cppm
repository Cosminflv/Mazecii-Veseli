export module Timer;

#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

using Thread = std::thread;
using AtomicBool = std::atomic<bool>;
using ConditionVariable = std::condition_variable;
using Mutex = std::mutex;
using TimerCallback = std::function<void()>;


export class _declspec(dllexport) Timer
{
public:
	//Constructors
	Timer(int total_minutes);


	//Flow of the timer
	void StartTimer();
	void StopTimer();
	void ResetTimer();

private:
	Thread m_thread;

	Mutex m_mutex;

	AtomicBool m_running;

	std::chrono::milliseconds m_initialTime;
	std::chrono::milliseconds m_remainingTime;
	std::chrono::milliseconds m_toDecreaseTime;
	std::chrono::milliseconds m_timerResolution;

	TimerCallback m_notifyChange;

};