#pragma once

#include <memory>
#include <iostream>
#include <chrono>
#include <concepts>
#include <map>
#include <any>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/printf.h>

template <typename T> class IProgressable;

template <typename T>
concept Progressable = std::is_base_of_v<IProgressable<T>, T>;

template <typename T, typename ...> class Progressbar;


template <typename T, typename ...>
class Progressbar
{
public:
    Progressbar() = default;

    void registerProgressable(T& object, const std::string& uuid)
    {
        auto p = std::pair<std::string, T&>(uuid, object);
        mRegisteredProgressables.insert(p);
    }

    void unregisterProgressable(T& object, const std::string& uuid)
    {
        mRegisteredProgressables.erase(uuid);
    }

    void draw()
    {
        for(auto const& progressable : mRegisteredProgressables)
        {
            std::cout << mRegisteredProgressables.size() << " " << progressable.second.getProgressCurrent() << std::endl;
        }
        //std::string progressbar = "\u2501";
//
	    //for(unsigned int progressbarChunk = 0; progressbarChunk < progressPercentage*0.3; progressbarChunk++ )
	    //{
	    //	progressbar = progressbar + "\u2501";
	    //}
//
	    //fmt::print("{3} {0}% {1} ETA {2}\r",
	    //	fmt::format(fmt::fg(fmt::color::yellow_green), "{:.{}f}", progressPercentage, 1),
	    //	fmt::format(fmt::fg(fmt::color::medium_aquamarine), "{:.{}f} P/Sec", progressPerSecond, 2),
	    //	fmt::format(fmt::fg(fmt::color::red), "{:.{}f} s", estimatedTime, 2),
	    //	fmt::format(fmt::fg(fmt::color::yellow_green), progressbar));
    //
	    ////std::fflush(stdout);

    }

private:
    std::map<std::string, T&> mRegisteredProgressables;
};

template<typename T>
class IProgressable
{
public:
    IProgressable(const std::shared_ptr<Progressbar<T>>& progressbar)
        : mProgressbarRef(progressbar) {}

public:
    virtual inline unsigned int getProgressCurrent() const = 0;
    virtual inline unsigned int getProgressFinishedValue() const = 0;

protected:
    void notifyProgressStarted(T& source)
    {
        mProgressbarRef->registerProgressable(source, mUUID);
        mStartTime = std::chrono::system_clock::now();
    }

    void notifyProgressFinished(T& source, const unsigned int currentProgress)
    {
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mStartTime).count();
        std::cout << std::endl;
        mProgressbarRef->unregisterProgressable(source, mUUID);
    }

    void notifyProgressChanged(T& source, const unsigned int currentProgress)
    {
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mStartTime).count();

        if(elapsedTime > 0)
		{
            mProgressbarRef->draw();
        }
    }

private:
    std::string mUUID;
    std::shared_ptr<Progressbar<T>> mProgressbarRef;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;

};