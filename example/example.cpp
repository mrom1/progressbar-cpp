#include <progressbar.hpp>

#include <thread>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

class SomeWorkload : public IProgressable<SomeWorkload>
{
public:
	SomeWorkload(const std::shared_ptr<Progressbar<SomeWorkload>> p) 
    : _currentProgress(0), _maximumProgress(10000), IProgressable<SomeWorkload>(p)
    {}

	virtual inline unsigned int getProgressCurrent() const override
	{
		return _currentProgress;
	}

	virtual inline unsigned int getProgressFinishedValue() const override
	{
		return _maximumProgress;
	}

	void doWork()
	{
        notifyProgressStarted(*this);
		do
		{
			doProgress();
			std::this_thread::sleep_for(100ms);
		}
		while(_currentProgress < _maximumProgress);
        notifyProgressFinished(*this, _currentProgress);
	}

private:
	void doProgress()
	{
		if(_currentProgress < _maximumProgress)
		{
			_currentProgress += 100;
            notifyProgressChanged(*this, _currentProgress);
		}
	}

private:
	unsigned int _currentProgress;
	unsigned int _maximumProgress;
};

class AnotherWorkload : public IProgressable<AnotherWorkload>
{
public:
	AnotherWorkload(const std::shared_ptr<Progressbar<AnotherWorkload>> p) 
    : _currentProgress(0), _maximumProgress(10000), IProgressable<AnotherWorkload>(p)
    {}

	virtual inline unsigned int getProgressCurrent() const override
	{
		return _currentProgress;
	}

	virtual inline unsigned int getProgressFinishedValue() const override
	{
		return _maximumProgress;
	}

	void doWork()
	{
        notifyProgressStarted(*this);
		do
		{
			doProgress();
			std::this_thread::sleep_for(100ms);
		}
		while(_currentProgress < _maximumProgress);
        notifyProgressFinished(*this, _currentProgress);
	}

private:
	void doProgress()
	{
		if(_currentProgress < _maximumProgress)
		{
			_currentProgress += 100;
            notifyProgressChanged(*this, _currentProgress);
		}
	}

private:
	unsigned int _currentProgress;
	unsigned int _maximumProgress;
};

int main()
{
    auto p = std::make_shared<Progressbar<SomeWorkload>>();
	auto w1 = std::make_shared<SomeWorkload>(p);
	auto f1 = std::async(&SomeWorkload::doWork, w1);
    //auto w2 = std::make_shared<SomeWorkload>();
	//auto f2 = std::async(&SomeWorkload::doWork, w2);

    f1.get();
    //f2.get();
    return 0;
}