// 3587. 最小相邻交换至奇偶交替（Minimum Adjacent Swaps to Alternate Parity）
// 核心思路：记录奇偶元素各自的下标，若数量差超过 1 则无解；否则让较少的一类（或两类取优）依次填满目标奇偶位，交换次数等于下标位移之和。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为数组长度。
class Solution {  // 定义题解类
public:  // 公有接口，判题器从这里调用
    int minSwaps(vector<int>& nums) {  // 求使奇偶交替的最少相邻交换次数
        vector<int> pos[2];  // pos[0] 存偶数的下标，pos[1] 存奇数的下标
        for (int i = 0; i < nums.size(); ++i) {  // 遍历数组，按下标收集两类元素的位置
            pos[nums[i] & 1].push_back(i);  // 把当前下标放入对应奇偶性的位置表
        }  // 结束收集
        if (abs(int(pos[0].size() - pos[1].size())) > 1) {  // 两类数量差超过 1 时无法交替排列
            return -1;  // 返回无解
        }  // 结束可行性判断
        auto calc = [&](int k) {  // 计算把 k 类元素依次放到偶数下标 0,2,4... 上的交换代价
            int res = 0;  // 累计交换次数
            for (int i = 0; i < nums.size(); i += 2) {  // 枚举目标偶数下标 0,2,4...
                res += abs(pos[k][i / 2] - i);  // 第 i/2 个 k 类元素要移动到下标 i，位移即交换次数
            }  // 结束累计
            return res;  // 返回该方案的交换次数
        };  // 结束 lambda
        if (pos[0].size() > pos[1].size()) {  // 偶数更多时只能从偶数开始交替
            return calc(0);  // 返回偶数占奇数位的方案
        }  // 结束分支
        if (pos[0].size() < pos[1].size()) {  // 奇数更多时只能从奇数开始交替
            return calc(1);  // 返回奇数占奇数位的方案
        }  // 结束分支
        return min(calc(0), calc(1));  // 两类数量相等时两种方案取更小值
    }  // 结束函数
};  // 结束类定义
