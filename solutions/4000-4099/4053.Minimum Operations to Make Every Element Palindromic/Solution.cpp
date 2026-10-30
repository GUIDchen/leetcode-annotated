// 题目：4053. 使每个元素变为回文数的最少操作次数（Minimum Operations to Make Every Element Palindromic）
// 思路：每次操作只能把元素 +2 或 -2，奇偶性始终不变，所以每个元素只能落到与它同奇偶的回文数上；先枚举 1..10^5 作为回文的“半边”，拼出所有 2k 位与 2k-1 位回文数并按奇偶分桶排序，再对每个元素二分找同奇偶的最近回文数，数值距离除以 2 就是操作次数。
// 时间复杂度：O(M log M + n log M)，M 为预计算出的回文数个数（约 2×10^5），排序只做一次、每次查询二分；空间复杂度：O(M)，用于保存全部回文数与两个奇偶桶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minOperations(vector<int>& nums) {  // nums：待变成回文数的数组；返回最少操作次数（每次把某个元素 +2 或 -2）
        static vector<long long> ps[2];  // ps[0] 存偶数回文数、ps[1] 存奇数回文数；static 让预计算在多次调用间只做一次
        if (ps[0].empty()) {  // 桶为空说明还没预处理过，只有第一次调用会进入
            for (long long i = 1; i <= 100000; ++i) {  // 枚举“半边” i，用它同时拼出偶数位与奇数位回文数
                string s = to_string(i);  // i 的十进制串作为回文的前半段（奇数位回文时含中间位）
                string t1 = s;  // 复制一份用于反转，拼偶数位回文
                reverse(t1.begin(), t1.end());  // t1 是 s 的反转，s + t1 就是回文
                string t2 = s.substr(0, s.size() - 1);  // 去掉末位后再作为奇数位回文的后半段
                reverse(t2.begin(), t2.end());  // t2 是去末位后反转的结果，s + t2 长度只比 s + t1 少 1
                long long x = stoll(s + t1);  // 拼出 2k 位的偶数位回文数
                ps[x & 1].push_back(x);  // 按奇偶放进对应的桶（下标就是 x & 1）
                long long y = stoll(s + t2);  // 拼出 2k-1 位的奇数位回文数
                ps[y & 1].push_back(y);  // 同样按奇偶入桶
            }  // 预处理枚举结束
            sort(ps[0].begin(), ps[0].end());  // 偶数桶升序排序，便于二分
            sort(ps[1].begin(), ps[1].end());  // 奇数桶升序排序，便于二分
        }  // 预处理结束，后续调用可直接查表
        long long ans = 0;  // ans 累计所有元素变成回文数所需的最少操作次数
        for (int x : nums) {  // 逐个元素寻找与它同奇偶的最近回文数
            auto& p = ps[x & 1];  // 每次操作改变 2，奇偶性不变，只可能变成同奇偶的回文数
            auto it = lower_bound(p.begin(), p.end(), x);  // 二分找到第一个大于等于 x 的同奇偶回文数
            long long t = LLONG_MAX;  // t 记录 x 到最近回文数的数值距离，先置为无穷大
            if (it != p.end()) {  // 右侧存在不小于 x 的回文数
                t = *it - x;  // 右侧候选的距离
            }  // 右侧分支结束
            if (it != p.begin()) {  // 左侧还存在小于 x 的同奇偶回文数
                t = min(t, (long long) x - *prev(it));  // 与左侧候选比较，取更小的距离
            }  // 左侧分支结束
            ans += t / 2;  // 每次操作改变 2，操作次数就是数值距离除以 2
        }  // 所有元素处理完毕
        return ans;  // 返回最少操作总数
    }  // 方法结束
};  // 类定义结束
