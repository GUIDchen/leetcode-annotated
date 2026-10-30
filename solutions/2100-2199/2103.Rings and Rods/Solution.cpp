// 题目：2103. 环和杆（Rings and Rods）
// 思路：红/绿/蓝分别编码成 1/2/4 三个二进制位，把每根杆上的颜色位或起来，最后数掩码等于 7 的杆。
// 时间复杂度：O(n)，一次扫描字符串；空间复杂度：O(1)，只有固定大小的映射表和 10 个掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPoints(string rings) {  // rings 形如 "R0G1B2"，每两个字符是一环，返回三色齐全的杆数
        int d['Z']{['R'] = 1, ['G'] = 2, ['B'] = 4};  // 指定初始化器：直接建立字符到二进制位的映射，'R'→1、'G'→2、'B'→4
        int mask[10]{};  // 每根杆的颜色掩码，值初始化保证全为 0
        for (int i = 0, n = rings.size(); i < n; i += 2) {  // 每次前进两个字符，长度只求一次缓存到 n
            int c = rings[i];  // 当前环的颜色字符
            int j = rings[i + 1] - '0';  // 当前环所在杆号
            mask[j] |= d[c];  // 把这种颜色对应的位并入该杆掩码
        }
        return count(mask, mask + 10, 7);  // 用 std::count 统计掩码恰好等于 7（三色齐全）的杆数
    }
};