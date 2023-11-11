module Timer;

static std::chrono::milliseconds TimeInMillis(const std::chrono::steady_clock::time_point& initial_time)
{
	auto current_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
}

Timer::Timer(int total_minutes)
	: m_initialTime{ total_minutes * 60 }
	, m_running{false}
	, m_timerResolution{1}
	, m_toDecreaseTime{0}
{
}

Timer::~Timer()
{
	m_running = false;

	if (m_thread.joinable()) {
		m_thread.join();
	}
}

void Timer::SetNotifyChange(TimerCallback newFunc)
{
	m_notifyChange = newFunc;
}

void Timer::SetTimerResolution(int ms)
{
	m_timerResolution = static_cast<std::chrono::milliseconds>(ms);
}

void Timer::StartTimer()
{
	m_running = true;
	
	m_cv.notify_all();

	if (!m_thread.joinable()) {
		m_thread = std::thread(&Timer::Run, this);
	}
}

void Timer::Run()
{
	while (m_running)
	{
		auto initial_time = std::chrono::steady_clock::now();

		std::unique_lock lk(m_mutex);
		m_cv.wait_for(lk, m_timerResolution, [&] { return !m_running; });

		auto elapsedTime = TimeInMillis(initial_time);
		m_toDecreaseTime += elapsedTime;

		initial_time = std::chrono::steady_clock::now();

		m_remainingTime = elapsedTime < m_remainingTime ? m_remainingTime - elapsedTime : std::chrono::milliseconds{ 0 };

		if (IsTimeExpired())
		{
			StopTimer();
		}

		m_notifyChange();
	}
}

