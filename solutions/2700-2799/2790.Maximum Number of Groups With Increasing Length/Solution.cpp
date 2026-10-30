// 题目：2790. 长度递增组的最大数目（Maximum Number of Groups With Increasing Length）
// 思路：升序排序后按顺序累加剩余可用量 s，s 足够再凑一个长度 k+1 的组时就令 k 加一并扣掉 k 个消耗，贪心得到最大组数。
// 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxIncreasingGroups(vector<int>& usageLimits) {  // usageLimits[i] 表示数字 i 最多可以使用的次数
        sort(usageLimits.begin(), usageLimits.end());  // 升序排序：可用次数少的数字优先用来填充较短的组
        int k = 0;  // k：当前已经能构造出的组数，也就是最终答案
        long long s = 0;  // s：尚未被消耗掉的可用次数总和（long long 防止累加溢出）
        for (int x : usageLimits) {  // 按排序后的顺序依次处理每种数字
            s += x;  // 把当前数字的可用次数并入剩余总量
            if (s > k) {  // 剩余量足够再凑出一个长度 k+1 的组
                ++k;  // 组数加一
                s -= k;  // 新组至少消耗 k 个元素，贪心地按最小需求扣除
            }  // if 结束
        }  // for 结束
        return k;  // 返回能构造的最大组数
    }  // 方法结束
};  // 类定义结束