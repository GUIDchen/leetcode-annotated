// 题目：3152. 特殊数组 II（Special Array II）
// 思路：预处理出每个下标所属「奇偶交替连续段」的左端点 d[i]，询问 [l, r] 只需判断 d[r] <= l。
// 时间复杂度：O(n + q)，预处理一遍加逐个询问；空间复杂度：O(n)，需要 d 数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {  // nums：原数组；queries：若干询问区间，返回每个区间是否为特殊子数组
        int n = nums.size();  // 数组长度
        vector<int> d(n);  // d[i] 记录 i 所在奇偶交替段的起始下标
        iota(d.begin(), d.end(), 0);  // 初始时每个位置各自成段，起点就是它自己
        for (int i = 1; i < n; ++i) {  // 从左到右递推每个位置的段起点
            if (nums[i] % 2 != nums[i - 1] % 2) {  // 相邻两数奇偶不同，说明可以与前一段接上
                d[i] = d[i - 1];  // 与左邻居同段，继承它的段起点
            }
        }
        vector<bool> ans;  // 保存每个询问的答案
        for (auto& q : queries) {  // 逐个处理询问区间 [q[0], q[1]]
            ans.push_back(d[q[1]] <= q[0]);  // 右端点的段起点不晚于 q[0]，整段都落在区间内，即为特殊子数组
        }
        return ans;  // 按询问顺序返回结果
    }
};