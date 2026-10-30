// 题目：1702. 修改后的最大二进制字符串（Maximum Binary String After Change）
// 思路：第一个 0 之前的 1 无法移动；此后每多一个 0 就能把它前面的 0 变成 1、自己变成最后一个 0，所以最靠前的 0 的位置是 k，最终形态是 k 个 1 + 0 + 剩余 1。
// 时间复杂度：O(n)，扫描两遍字符串；空间复杂度：O(n)，用于构造返回的字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string maximumBinaryString(string binary) {  // binary 是只含 '0'/'1' 的字符串
        int k = binary.find('0');  // 找到第一个 '0' 的下标，它之前的所有 '1' 都动不了
        if (k == binary.npos) {  // 找不到 '0' 说明全是 '1'
            return binary;  // 全 1 已是最大字典序，直接原样返回
        }
        int n = binary.size();  // 字符串长度，后面构造结果要用
        for (int i = k + 1; i < n; ++i) {  // 从第一个 '0' 之后继续扫描
            if (binary[i] == '0') {  // 每遇到一个额外的 '0'
                ++k;  // 最终那个唯一的 '0' 就向后挪一位，前缀 1 的个数加一
            }
        }
        return string(k, '1') + '0' + string(n - k - 1, '1');  // 拼成 k 个 1、一个 0、再补齐剩余的 1
    }
};