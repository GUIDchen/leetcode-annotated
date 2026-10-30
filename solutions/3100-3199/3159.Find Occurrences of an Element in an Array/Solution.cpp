// 题目：3159. 查询数组中元素的出现位置（Find Occurrences of an Element in an Array）
// 核心思路：先一次遍历记录值等于 x 的所有下标（按下标从小到大），再对每个询问取第 queries[i] 次出现的下标；次数越界则返回 -1。
// 时间复杂度：O(n+m)，n 为数组长度、m 为询问数；空间复杂度：O(n)，存 x 的全部下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) {  // nums：原始数组；queries：若干「第几次出现」的询问；x：被查询的元素值
        vector<int> ids;  // 按顺序记录 x 在 nums 中每次出现的下标
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描整个数组
            if (nums[i] == x) {  // 遇到等于 x 的位置
                ids.push_back(i);  // 把下标追加进 ids，保证 ids 天然升序
            }  // if 结束
        }  // 扫描结束
        vector<int> ans;  // 存放每个询问的答案
        for (int& i : queries) {  // 逐个处理询问，用引用避免拷贝
            ans.push_back(i - 1 < ids.size() ? ids[i - 1] : -1);  // 第 i 次出现对应下标 ids[i-1]；不存在时返回 -1
        }  // 询问处理结束
        return ans;  // 返回所有询问的答案
    }  // 方法结束
};  // 类定义结束