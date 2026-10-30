// 题目：2343. 裁剪数字后查询第 K 小的数字（Query Kth Smallest Trimmed Number）
// 思路：对每个查询截取所有数字的末尾 trim 位，把「裁剪后的字符串, 原下标」配对排序；pair 默认先比字符串再比下标，天然满足数值相同时下标小的排前面，第 k 小就是排序后第 k-1 个元素的原下标。
// 时间复杂度：O(q · n log n · L)，q 为查询数、L 为字符串长度（字符串比较代价）；空间复杂度：O(n)，用于存放配对数组与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {  // nums：数字字符串数组；queries：每个查询是 {k, trim}
        int n = nums.size();  // 记录数字个数，后续所有循环都以它为界
        vector<pair<string, int>> t(n);  // 复用同一个配对数组，避免每个查询都重新分配
        vector<int> ans;  // ans 按查询顺序收集答案
        for (auto& q : queries) {  // 逐个查询独立处理
            int k = q[0], trim = q[1];  // k 是第几小（1 起），trim 是要保留的末尾位数
            for (int j = 0; j < n; ++j) {  // 为本查询填充所有数字的「裁剪结果, 原下标」
                t[j] = {nums[j].substr(nums[j].size() - trim), j};  // substr 从 size()-trim 开始截到末尾，得到低 trim 位；题目保证 trim 不超过长度
            }  // 填充结束
            sort(t.begin(), t.end());  // pair 的默认比较：先比裁剪字符串，相等时再比原下标，正好符合题目要求的稳定顺序
            ans.push_back(t[k - 1].second);  // 第 k 小对应下标 k-1，记录它的原下标
        }  // 查询处理结束
        return ans;  // 按查询顺序返回全部答案
    }  // 方法结束
};  // 类结束