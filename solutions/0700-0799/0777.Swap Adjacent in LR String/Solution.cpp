// 题目：777. 在 LR 字符串中交换相邻字符（Swap Adjacent in LR String）
// 思路：'X' 相当于空位，'R' 只能整体右移、'L' 只能整体左移；忽略全部 'X' 后两串字符序列必须完全相同，且每个字符在 start 中的位置不能越过它在 end 中的位置（'L' 不能偏右、'R' 不能偏左）。
// 时间复杂度：O(n)，双指针各扫一遍字符串；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canTransform(string start, string end) {  // start：初始字符串；end：目标字符串；返回能否只靠相邻交换把 start 变成 end
        int n = start.size();  // n：字符串长度，题目保证两个串等长，也是双指针扫到末尾的边界
        int i = 0, j = 0;  // i 扫 start、j 扫 end，二者始终指向各自下一个非 'X' 字符
        while (true) {  // 外层循环每轮对齐一对非 'X' 字符，真正的出口在下面的各个 return
            while (i < n && start[i] == 'X') ++i;  // 跳过 start 中的 'X'：'X' 可自由滑动，不参与配对
            while (j < n && end[j] == 'X') ++j;  // 跳过 end 中的 'X'，让 i、j 都落在第 k 个非 'X' 字符上
            if (i == n && j == n) return true;  // 两边同时扫完：所有非 'X' 字符一一配对成功，可以转换
            if (i == n || j == n || start[i] != end[j]) return false;  // 只有一边先扫完（非 'X' 个数不同）或当前字符不同（'L'/'R' 顺序不同），都不可能转换
            if (start[i] == 'L' && i < j) return false;  // 'L' 只能与左边的 'X' 交换而左移；若它在 start 中更靠右，就永远追不上 end 的位置
            if (start[i] == 'R' && i > j) return false;  // 'R' 只能与右边的 'X' 交换而右移；若它在 start 中更靠左，同样到不了 end 的位置
            ++i;  // 这一对字符校验通过，start 指针后移一位
            ++j;  // end 指针同步后移一位，准备配对下一对
        }  // 外层 while 结束
    }  // canTransform 方法结束
};  // Solution 类定义结束