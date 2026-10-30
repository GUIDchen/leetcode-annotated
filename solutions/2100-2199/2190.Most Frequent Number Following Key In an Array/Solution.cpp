// 题目：2190. 数组中紧跟 key 之后出现最频繁的数字（Most Frequent Number Following Key In an Array）
// 思路：扫描到 nums[i] == key 时，把 nums[i+1] 的计数加一，并随时维护出现次数最多的那个数字。
// 时间复杂度：O(n)；空间复杂度：O(1000) = O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mostFrequent(vector<int>& nums, int key) {  // nums：输入数组；key：需要关注的数字
        int cnt[1001]{};  // 计数数组，题目数据范围是 1..1000，值初始化为 0
        int ans = 0, mx = 0;  // ans：当前出现次数最多的数字；mx：对应的最大次数
        for (int i = 0; i < nums.size() - 1; ++i) {  // 只遍历到倒数第二个元素，保证 i+1 不越界
            if (nums[i] == key) {  // 找到 key 出现的位置
                if (mx < ++cnt[nums[i + 1]]) {  // 先给紧随其后的数字计数加一，再与当前最大值比较
                    mx = cnt[nums[i + 1]];  // 出现次数刷新
                    ans = nums[i + 1];  // 记录这个新的最频繁数字
                }  // 内层 if 结束
            }  // 外层 if 结束
        }  // 循环结束
        return ans;  // 返回答案（题目保证存在）
    }  // 方法结束
};  // 类定义结束