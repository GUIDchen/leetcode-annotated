// 题目：1108. IP 地址无效化（Defanging an IP Address）
// 思路：从字符串末尾往前扫描，遇到 '.' 就用 replace 原地替换成 "[.]"；倒序保证已处理位置的下标不会因长度变化而错位。
// 时间复杂度：O(n^2)，replace 需要搬移后续字符，最坏每个点号都搬一次；空间复杂度：O(1)，除返回的字符串外只用常数额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题接口
    string defangIPaddr(string address) {  // address 是形如 1.1.1.1 的 IPv4 地址串
        for (int i = address.size(); i >= 0; --i) {  // 从末尾（含结尾 '\0' 位置）往前扫，倒序可避免替换后下标失效
            if (address[i] == '.') {  // 找到需要替换的点号
                address.replace(i, 1, "[.]");  // 把 1 个字符的点号原地替换成 3 个字符的 "[.]"
            }
        }
        return address;  // 返回无效化处理后的字符串
    }
};