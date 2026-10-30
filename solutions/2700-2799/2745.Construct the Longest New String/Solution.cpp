// 题目：2745. 构造最长的新字符串（Construct the Longest New String）
// 核心思路："AA" 与 "BB" 只能交替夹在中间，"AB" 用来收尾；x 与 y 相差超过 1 时以较少的一方为基准，否则全部用上。
// 时间复杂度：O(1)，只有常数次算术运算；空间复杂度：O(1)，不使用额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestString(int x, int y, int z) {  // x、y、z 分别是 "AA"、"BB"、"AB" 的可用个数
        if (x < y) {  // "BB" 更多：最多只能配 x 个 "AA"，再多放一个 "BB" 收尾
            return (x * 2 + z + 1) * 2;  // 可用字符串个数乘以 2 得到字符长度
        }
        if (x > y) {  // "AA" 更多：对称地以 y 为基准，再多放一个 "AA" 收尾
            return (y * 2 + z + 1) * 2;  // 可用字符串个数乘以 2 得到字符长度
        }
        return (x + y + z) * 2;  // 两者数量相等，所有字符串都能用上，乘以 2 得到字符长度
    }
};