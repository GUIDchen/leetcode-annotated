// 题目：443. 压缩字符串（String Compression）
// 思路：双指针原地压缩，i 指向当前连续段的起点，j 向右扫到该段结束；把字符与十进制计数依次写回数组前部，k 是写指针。
// 复杂度：时间复杂度 O(n)，每个字符只被读写常数次；空间复杂度 O(1)，只用了常数个额外变量。
class Solution {  // 题解类：字符串原地压缩
public:  // 公开部分
    int compress(vector<char>& chars) {  // chars 是字符数组（原地修改），返回压缩后的长度
        int k = 0, n = chars.size();  // k 是写指针，n 是原数组长度
        for (int i = 0, j = i + 1; i < n;) {  // i 是当前连续段的起点，j 从 i+1 开始向右找段尾
            while (j < n && chars[j] == chars[i])  // 一直右移，直到字符变化或走出数组
                ++j;  // 段尾继续右移
            chars[k++] = chars[i];  // 先写字符本身，写指针后移
            if (j - i > 1) {  // 出现次数大于 1 时才需要写计数
                for (char c : to_string(j - i)) {  // 计数可能有多位，转成字符串后逐位写入
                    chars[k++] = c;  // 写入一位数字并后移写指针
                }  // 计数写完
            }  // 闭合 if (j - i > 1)
            i = j;  // 跳到下一段的起点
        }  // 所有连续段处理完毕
        return k;  // 写指针的位置就是压缩后的长度
    }  // compress 方法结束
};  // Solution 类定义结束