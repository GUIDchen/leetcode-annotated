// 题目：1845. 座位预约管理系统（Seat Reservation Manager）
// 思路：用最小堆维护所有可用座位编号；reserve 弹出堆顶即当前最小可用号，unreserve 把归还的号重新压回堆中。
// 时间复杂度：构造 O(n)；reserve/unreserve 均为 O(log n)；空间复杂度：O(n)，堆中最多保存 n 个座位号。
class SeatManager {  // 题目要求的座位管理器类
public:  // 对外接口
    SeatManager(int n) {  // 构造：座位编号从 1 到 n 全部空闲
        for (int i = 1; i <= n; ++i) {  // 依次把每个座位号放入最小堆
            q.push(i);  // 入堆后堆顶始终是最小的可用座位号
        }
    }

    int reserve() {  // 预约并返回编号最小的可用座位
        int seat = q.top();  // 取堆顶：当前最小的可用座位号
        q.pop();  // 该座位被占用，从可用集合中移除
        return seat;  // 返回预约到的座位号
    }

    void unreserve(int seatNumber) {  // 释放指定座位，使其重新可用
        q.push(seatNumber);  // 归还的座位号重新入堆，堆自动恢复有序
    }

private:  // 内部数据成员
    priority_queue<int, vector<int>, greater<int>> q;  // 小根堆：堆顶永远是编号最小的空闲座位
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */