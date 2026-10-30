// 题目：4080. 设计公交车座位预订系统（Design Bus Seat Booking System）
// 核心思路：把座位拆成「第 i 排、第 j 列」并用 cost_data 记录该座位当前计入的费用（0 表示空座）；A 座与相邻的 B 座同时被占、D 座与相邻的 C 座同时被占时费用升为 3，否则为 1。同时维护已预订座位数 min_tot 与总费用 tot，toggle 每次只做常数次更新。
// 复杂度：toggle / getTotalTime / getMinTime 均为 O(1) 时间；空间 O(n)，n 为排数，每排固定 4 个座位。
class BusBooking {  // 公交车座位预订系统
private:  // 私有成员：内部状态不对外暴露
    int tot;  // tot：当前所有已预订座位按实际冲突情况累计的总耗时
    int min_tot;  // min_tot：当前已预订的座位个数，也是最优安排下的最小总耗时
    vector<array<int, 4>> cost_data;  // cost_data[i][j]：第 i 排第 j 列座位当前计入的费用，0 表示空座

public:  // 公开接口：构造函数与三个查询/操作函数
    BusBooking(int n) {  // 构造函数，n 为公交车的排数
        tot = 0;  // 初始没有任何预订，总耗时为 0
        min_tot = 0;  // 初始已预订座位数为 0
        cost_data = vector<array<int, 4>>(n, {0, 0, 0, 0});  // 开辟 n 排、每排 4 个座位，费用全部初始化为 0
    }  // 构造函数结束

    void toggle(string seat) {  // 切换一个座位的预订状态，seat 形如 "A1"、"D10"
        int i = 0;  // i 用来累加座位号中的排号数字
        for (int k = 1; k < seat.size(); k++) {  // 从第 2 个字符开始逐位解析排号
            i = i * 10 + (seat[k] - '0');  // 十进制左移累加，字符减去 '0' 得到对应数字
        }  // 排号解析结束
        i -= 1;  // 排号从 1 开始，转成从 0 开始的下标
        int j = seat[0] - 'A';  // 首字母 A/B/C/D 映射为列下标 0/1/2/3

        if (cost_data[i][j] > 0) {  // 该座位已有费用，说明它是被预订过的，这次操作即为取消
            min_tot -= 1;  // 已预订座位数减一
            tot -= cost_data[i][j];  // 总耗时减去该座位当初计入的费用
            cost_data[i][j] = 0;  // 把该座位标记回空座
            return;  // 取消完成，无需再处理新增逻辑
        }  // 取消分支结束

        int cost = 1;  // 默认该座位单独占一个时间单位，费用为 1
        if ((j == 0 && cost_data[i][1] > 0) || (j == 3 && cost_data[i][2] > 0)) {  // A 座与相邻的 B 座同时被占，或 D 座与相邻的 C 座同时被占时，二者必须错开，费用变 3
            cost = 3;  // 存在相邻冲突，本次预订需要 3 个时间单位
        }  // 相邻冲突判断结束
        min_tot += 1;  // 新预订一个座位，已预订座位数加一
        tot += cost;  // 总耗时累加本次座位的费用
        cost_data[i][j] = cost;  // 记录该座位当前计入的费用，供后续取消与冲突判断使用
    }  // toggle 结束

    int getTotalTime() {  // 返回按当前预订顺序累计的总耗时
        return tot;  // 直接返回维护好的总费用
    }  // getTotalTime 结束

    int getMinTime() {  // 返回最优安排下的最小总耗时
        return min_tot;  // 每个座位各占一个时间单位，最小值就等于已预订座位数
    }  // getMinTime 结束
};  // BusBooking 类结束

/**
 * Your BusBooking object will be instantiated and called as such:  // 判题器的调用方式示例（块注释内的原文保持不变）
 * BusBooking* obj = new BusBooking(n);  // 用排数 n 实例化对象
 * obj->toggle(seat);  // 切换座位 seat 的预订状态
 * int param_2 = obj->getTotalTime();  // 取总耗时
 * int param_3 = obj->getMinTime();  // 取最小耗时
 */