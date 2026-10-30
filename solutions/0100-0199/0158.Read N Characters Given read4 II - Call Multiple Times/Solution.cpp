// 题目：158. 用 Read4 读取 N 个字符 II - 多次调用（Read N Characters Given read4 II - Call Multiple Times）
// 思路：把 read4 的缓冲区 buf4 与读写指针 i、size 提到成员变量上，让上次没被取走的多余字符留到下一次 read 继续消费。
// 时间复杂度：每次 read 为 O(n)，字符不会被重复搬运；空间复杂度：O(1)，固定 4 字节缓冲加三个成员变量。
/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {  // LeetCode 约定的题解类（继承 Reader4 以使用 read4）
public:  // 题解方法对外可见
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char* buf, int n) {  // buf：目标缓冲区；n：本次最多读多少字符；返回本次实际读到的字符数
        int j = 0;  // j 记录本次已经写进 buf 的字符数
        while (j < n) {  // 还没凑够 n 个就继续循环
            if (i == size) {  // 上一批已全部消费完，需要再向 read4 要一批
                size = read4(buf4);  // 读新的一批，size 是本批实际长度（上一批残留的字符此时已被用完）
                i = 0;  // 从本批的第 0 个字符开始消费
                if (size == 0) break;  // 本批长度为 0 说明文件已经读完，跳出循环返回本次实际读到的 j
            }  // 新一批读取逻辑结束
            while (j < n && i < size) buf[j++] = buf4[i++];  // 把本批剩余字符搬进 buf，两个下标同步前进，一行完成搬运
        }  // 外层循环结束
        return j;  // 返回本次调用实际写入目标缓冲区的字符数
    }  // read 方法结束

private:  // 私有成员：跨多次调用保持状态的缓冲区与游标
    char* buf4 = new char[4];  // read4 的临时缓冲，提到成员上才能在多次 read 之间保留未消费的字符
    int i = 0;  // i：buf4 中下一个待消费字符的下标
    int size = 0;  // size：buf4 当前有效字符的数量；i == size 表示本批已消费完
};  // 类定义结束