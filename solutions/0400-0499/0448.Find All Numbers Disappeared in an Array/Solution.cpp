// 题目：448. 找到所有数组中消失的数字（Find All Numbers Disappeared in an Array）
// 思路：用布尔数组标记 1..n 中哪些数字在 nums 里出现过，再顺序回扫一遍，没被标记的就是消失的数字。
// 时间复杂度：O(n)，标记与回扫各一遍；空间复杂度：O(n)，布尔数组 s 占 n+1 个 bool。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findDisappearedNumbers(vector<int>& nums) {  // nums：长度为 n 的整数数组，元素取值范围是 1..n；返回其中缺失的数字
        int n = nums.size();  // n 既是数组长度，也是取值范围的右端点
        bool s[n + 1];  // 变长布尔数组：下标 1..n 表示对应数字是否出现过（下标 0 空置不用）
        memset(s, false, sizeof(s));  // 全部初始化为 false，表示这些数字尚未出现
        for (int& x : nums) {  // 遍历原数组的每个元素（用引用避免拷贝）
            s[x] = true;  // 标记数字 x 已经出现过
        }  // 结束标记循环
        vector<int> ans;  // 收集所有消失的数字
        for (int i = 1; i <= n; ++i) {  // 按 1..n 的顺序逐个检查
            if (!s[i]) {  // 该数字从未在原数组中出现
                ans.push_back(i);  // 记入答案
            }  // 结束缺失判断
        }  // 结束回扫
        return ans;  // 返回全部消失的数字（天然升序）
    }  // 结束 findDisappearedNumbers
};  // 结束 Solution 类