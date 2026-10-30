// 题目：2459. 通过移动项目到空白区域来排序数组（Sort Array by Moving Items to Empty Space）
// 思路：把数组看成置换，空位（值 0）每进入一个置换环就付出「环长 + 1」次操作；分别考虑目标为恒等映射与整体左移两种映射，取较小值。
// 时间复杂度：O(n)，两次遍历置换环；空间复杂度：O(n)，访问标记数组与复制出的临时数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sortArray(vector<int>& nums) {  // nums：以 0 表示空白位的排列
        int n = nums.size();  // 数组长度，也就是元素 0..n-1 的个数
        auto f = [&](vector<int>& nums, int k) {  // 通用代价函数：k 表示空白位在目标映射下应处的下标
            vector<bool> vis(n);  // 访问标记：记录每个位置是否已被某个置换环统计过
            int cnt = 0;  // 操作次数累计
            for (int i = 0; i < n; ++i) {  // 枚举每个位置，寻找还没处理过的置换环
                if (i == nums[i] || vis[i]) continue;  // 已经就位或已被之前的环统计，跳过
                int j = i;  // 从当前未访问的位置出发沿置换行走
                ++cnt;  // 每个非平凡环先付 1 次操作，相当于把空白位挪进这个环
                while (!vis[j]) {  // 沿 j -> nums[j] 环行，直到回到已访问的位置
                    vis[j] = true;  // 标记该位置已统计
                    ++cnt;  // 环上每个元素都要被移动一次
                    j = nums[j];  // 跳到当前元素应在的目标位置
                }
            }
            if (nums[k] != k) cnt -= 2;  // 空白位最终不在 k 处时，环路首尾可以省掉 2 次操作
            return cnt;  // 返回这种目标映射下的总操作数
        };  // 结束代价函数 lambda

        int a = f(nums, 0);  // 方案一：目标为恒等映射，空白 0 应回到下标 0
        vector<int> arr = nums;  // 复制一份，避免破坏原数组
        for (int& v : arr) v = (v - 1 + n) % n;  // 方案二：整体循环左移一位，使空白 0 的目标下标变成 n-1
        int b = f(arr, n - 1);  // 方案二下空白位（原值 0）的目标下标是 n-1
        return min(a, b);  // 两种目标映射取更小的操作数
    }  // 结束 sortArray
};  // 结束 Solution 类