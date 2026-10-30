// 题目：179. 最大数（Largest Number）
// 思路：把所有数字转成字符串，按「a+b > b+a」的自定义比较器降序排序后依次拼接；若首串为 "0" 说明全是 0，直接返回 "0"。
// 时间复杂度：O(n log n * L)，每次比较要拼接长度为 L 的串；空间复杂度：O(n * L)，字符串数组的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string largestNumber(vector<int>& nums) {  // nums：待拼接的非负整数数组
        vector<string> vs;  // 存放每个整数的字符串形式
        for (int v : nums) vs.push_back(to_string(v));  // 逐个转字符串，供后续按字典序拼接比较
        sort(vs.begin(), vs.end(), [](string& a, string& b) {  // 用自定义比较器对整个数组排序
            return a + b > b + a;  // a 拼在 b 前更大时 a 应排前面，这样整体拼接结果最大
        });
        if (vs[0] == "0") return "0";  // 排完首位仍是 "0" 说明元素全为 0，返回单个 "0" 而不是 "00..."
        string ans;  // 保存最终拼接结果
        for (string v : vs) ans += v;  // 按排序好的顺序逐个拼接
        return ans;  // 返回最大数；用字符串避免超出整型范围
    }
};