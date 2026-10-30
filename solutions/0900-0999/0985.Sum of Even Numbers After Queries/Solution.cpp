// 题目：985. 查询后的偶数和（Sum of Even Numbers After Queries）
// 思路：先求初始偶数和，每个查询先减去旧值（若为偶数），加上 v 后再加回新值（若为偶数），并记录当前和。
// 时间复杂度：O(n+q)，每个元素和查询各处理一次；空间复杂度：O(q)，答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {  // nums 是原数组，queries 每项为 [加数, 下标]
        int s = 0;  // s 维护当前所有偶数之和
        for (int x : nums) {  // 遍历数组求初始偶数和
            if (x % 2 == 0) {  // 只有偶数才计入
                s += x;  // 累加该偶数
            }  // if 结束
        }  // 遍历结束
        vector<int> ans;  // ans 保存每次查询后的偶数和
        for (auto& q : queries) {  // 依次处理每个查询
            int v = q[0], i = q[1];  // q[0] 是加数 v，q[1] 是被修改的下标 i
            if (nums[i] % 2 == 0) {  // 旧值是偶数，先从和中剔除
                s -= nums[i];  // 减去旧值
            }  // if 结束
            nums[i] += v;  // 真正把 v 加到 nums[i] 上
            if (nums[i] % 2 == 0) {  // 新值是偶数，需要重新计入
                s += nums[i];  // 加上新值
            }  // if 结束
            ans.push_back(s);  // 记录本次查询后的偶数和
        }  // 查询循环结束
        return ans;  // 返回所有查询的答案
    }  // 方法结束
};  // 类定义结束