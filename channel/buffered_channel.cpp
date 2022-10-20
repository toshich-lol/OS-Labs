#include "buffered_channel.h"

BufferedChannel<int> bufferedChannel(5);

void ThreadFirstTest()
{
    bufferedChannel.Send(1);
    bufferedChannel.Send(2);
    bufferedChannel.Send(3);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bufferedChannel.Send(4);
    bufferedChannel.Send(5);
    bufferedChannel.Recv();
    bufferedChannel.Recv();
    bufferedChannel.Recv();
    bufferedChannel.Recv();
}
void ThreadSecondTest()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bufferedChannel.Recv();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bufferedChannel.Send(6);
    bufferedChannel.Send(7);
    bufferedChannel.Send(8);
    bufferedChannel.Close();
}

int main()
{
    std::thread thread1(ThreadFirstTest);
    std::thread thread2(ThreadSecondTest);
    thread1.join();
    thread2.join();
    return 0;
}