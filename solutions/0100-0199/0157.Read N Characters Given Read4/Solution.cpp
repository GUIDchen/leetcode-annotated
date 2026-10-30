// 题目：157. 用 Read4 读取 N 个字符（Read N Characters Given Read4）
// 思路：反复调用 read4 把最多 4 个字符读进临时数组 buf4，再逐个搬进目标 buf，凑够 n 个立刻返回；某批不足 4 个说明文件已读完。
// 时间复杂度：O(n)，最多搬运 n 个字符；空间复杂度：O(1)，额外只用长度为 4 的临时数组。
/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {  // LeetCode 约定的题解类（继承判题器提供的 Reader4，可调用 read4）
public:  // 题解方法对外可见
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char* buf, int n) {  // buf：目标缓冲区；n：最多要读的字符数；返回值是实际读到的字符数
        char buf4[4];  // 临时缓冲：read4 每次最多写入 4 个字符
        int i = 0, v = 5;  // i 记录已写入 buf 的字符数；v 初始化为 5 只是为了让外层 while 至少执行一次
        while (v >= 4) {  // v >= 4 表示上一批读满了 4 个，可能还有剩余数据，需要继续读
            v = read4(buf4);  // 调用 read4 读取下一批，v 是本批实际读到的字符数（0 表示文件结束）
            for (int j = 0; j < v; ++j) {  // 把本批的 v 个字符逐个搬进目标缓冲区
                buf[i++] = buf4[j];  // 先写入 buf 的当前位置，再让 i 自增指向下一个空位
                if (i >= n) {  // 已经凑够 n 个字符，不必继续读
                    return n;  // 按题目要求返回 n（实际读到也正是 n 个）
                }  // if 结束
            }  // 本批字符搬运完毕
        }  // 本批不足 4 个说明文件已读完，退出外层循环
        return i;  // 返回实际读到的字符总数（文件较短时可能小于 n）
    }  // read 方法结束
};  // 题解类定义结束