// 题目：3012. 通过操作使数组长度最小（Minimize Length of Array Using Operations）
// 思路：操作是「删掉 x 和 y，换入 x % y」。取全局最小值 mi：只要有某个数不能被 mi 整除，就能用余数造出比 mi 更小的数，最终把数组削到只剩 1 个；否则所有数都是 mi 的倍数，只能把最小值两两配对消掉，剩 ceil(cnt(mi)/2) 个。
// 时间复杂度：O(n)，两趟线性扫描数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumArrayLength(vector<int>& nums) {  // nums：输入数组；返回取模操作后数组可能达到的最小长度
        int mi = *min_element(nums.begin(), nums.end());  // mi 是数组最小值：任何 x % mi 的结果都落在 0..mi-1
        int cnt = 0;  // cnt 统计最小值 mi 在数组中出现了多少次
        for (int x : nums) {  // 遍历每个元素，检查它能否破坏 mi 的最小性
            if (x % mi) {  // x 不能被 mi 整除，余数就落在 1..mi-1，比 mi 更小
                return 1;  // 用这个更小的余数可以不断删减其它元素，最终只剩 1 个
            }  // if 语句结束
            cnt += x == mi;  // x == mi 成立时加 1：布尔值参与整数运算，统计最小值出现次数
        }  // 遍历结束，说明所有元素都是 mi 的倍数
        return (cnt + 1) / 2;  // 只能把 mi 两两配对消去，剩余个数向上取整
    }  // 方法结束
};  // 类定义结束