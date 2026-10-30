// 题目：1011. 在 D 天内送达包裹的能力（Capacity To Ship Packages Within D Days）
// 核心思路：二分答案：在重量最大值与总重量之间查找最小可行运力
// 复杂度：时间 O(n log(sum))，每次 check 线性扫描；空间 O(1)
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shipWithinDays(vector<int>& weights, int days) {  // weights：包裹重量（必须按给定顺序装运）；days：限定天数
        int left = 0, right = 0;  // 二分区间 [left, right]：答案一定落在其中
        for (auto& w : weights) {  // 遍历包裹重量，同时确定二分上下界
            left = max(left, w);  // 运力至少要能装下最重的那个包裹
            right += w;  // 运力取全部重量之和时，一天就能运完，必然是可行上界
        }  // 上下界确定完毕
        auto check = [&](int mx) {  // 局部函数：判断运力为 mx 时能否在 days 天内运完
            int ws = 0, cnt = 1;  // ws：当前这一船已装重量；cnt：已用天数（至少要用 1 天）
            for (auto& w : weights) {  // 按顺序装船，包裹顺序不能打乱
                ws += w;  // 尝试把当前包裹装上这一船
                if (ws > mx) {  // 超过运力，只能把它放到下一天
                    ws = w;  // 新的一天从当前包裹开始装
                    ++cnt;  // 使用天数加一
                }  // 超载判断结束
            }  // 所有包裹装完
            return cnt <= days;  // 用掉的天数不超过限定天数就说明运力足够
        };  // lambda 结束
        while (left < right) {  // 二分查找最小可行运力
            int mid = (left + right) >> 1;  // 取中点，右移一位等价于除以 2 向下取整
            if (check(mid)) {  // 中点可行，答案可能更小
                right = mid;  // 保留 mid 作为新的上界
            } else {  // 中点不可行，答案一定更大
                left = mid + 1;  // 排除 [left, mid]，从 mid+1 继续找
            }  // 分支结束
        }  // 区间收敛
        return left;  // left 就是使 check 成立的最小运力
    }  // 方法结束
};  // 类定义结束