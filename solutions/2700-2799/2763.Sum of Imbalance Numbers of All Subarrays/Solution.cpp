// 题目：2763. 所有子数组中不平衡数字之和（Sum of Imbalance Numbers of All Subarrays）
// 思路：枚举左端点 i，用有序多重集 s 保存当前子数组并增量维护不平衡数字 cnt；每插入 nums[j] 时按「右侧断开、左侧断开、左右被连上」三条规则更新 cnt，再把 cnt 累加到答案。
// 时间复杂度：O(n^2 log n)，共 O(n^2) 次插入，每次 O(log n)；空间复杂度：O(n)，有序集合最多保存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumImbalanceNumbers(vector<int>& nums) {  // nums 是输入数组，返回所有子数组的不平衡数字之和
        int n = nums.size();  // n 是数组长度
        int ans = 0;  // ans 累加所有子数组的不平衡数字，n <= 1000 时答案仍在 int 范围内
        for (int i = 0; i < n; ++i) {  // 枚举子数组左端点 i
            multiset<int> s;  // 每个左端点都新建一个有序集合，保存当前子数组的元素
            int cnt = 0;  // cnt 是当前子数组的不平衡数字，随右端点扩张增量维护
            for (int j = i; j < n; ++j) {  // 右端点 j 从 i 开始向右扩张；multiset 允许重复值
                auto it = s.lower_bound(nums[j]);  // lower_bound 找到第一个不小于 nums[j] 的位置，用它定位左右两侧的邻居
                if (it != s.end() && *it - nums[j] > 1) {  // 右侧邻居与 nums[j] 相差大于 1，说明插入后这里会多出一个断点
                    ++cnt;  // 不平衡数字加一
                }  // 右侧判断结束
                if (it != s.begin() && nums[j] - *prev(it) > 1) {  // 左侧邻居与 nums[j] 相差大于 1，同样会多出一个断点
                    ++cnt;  // 不平衡数字加一
                }  // 左侧判断结束
                if (it != s.end() && it != s.begin() && *it - *prev(it) > 1) {  // 左右两个邻居插入后变得相邻：若它们原本不相邻，之前统计的那个断点会被 nums[j] 连上
                    --cnt;  // 撤销这个被重复统计的断点
                }  // 撤销判断结束
                s.insert(nums[j]);  // 把 nums[j] 真正插入有序集合，作为后面元素的邻居
                ans += cnt;  // [i, j] 的不平衡数字就是 cnt，累加进答案
            }  // 以 i 为左端点的所有子数组都处理完了
        }  // 换成下一个左端点
        return ans;  // 返回所有子数组的不平衡数字之和
    }  // 方法结束
};  // 类定义结束