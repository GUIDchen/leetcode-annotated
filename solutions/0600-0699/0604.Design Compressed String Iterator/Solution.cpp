// 题目：604. 迭代压缩字符串（Design Compressed String Iterator）
// 思路：构造时把压缩串预解析成「字符 + 次数」的数组并记录指针 p，next 时逐个消耗次数，用完就前移 p。
// 时间复杂度：构造 O(L)、next/hasNext O(1)；空间复杂度：O(k)，k 为压缩串中不同字符的段数。
class StringIterator {  // 压缩字符串迭代器类
public:  // 对外提供的构造与迭代接口
    StringIterator(string compressedString) {  // 构造函数：把形如 a2b3 的压缩串预处理成字符与次数的序列
        int n = compressedString.size();  // 压缩串长度，作为扫描的边界
        int i = 0;  // 扫描下标，从压缩串开头开始
        while (i < n) {  // 每轮解析一段「字母 + 若干位数字」
            char c = compressedString[i];  // 当前段的字符就是这一位
            int x = 0;  // 该字符重复次数，先清零再按位累加
            while (++i < n && isdigit(compressedString[i])) {  // 先跳过字符本身，再逐位读取紧跟的数字
                x = x * 10 + (compressedString[i] - '0');  // 把字符型数字转成数值并接到已有的十进制数后面，支持多位数次数
            }  // 当前段的数字读取结束
            d.push_back({c, x});  // 把这一段（字符、次数）追加到预解析结果里
        }  // 整串解析完成
    }  // 构造函数结束

    char next() {  // 返回下一个字符，并把它的剩余次数减一
        if (!hasNext()) return ' ';  // 已经取完时按题目约定返回空格
        char ans = d[p].first;  // 记下当前段对应的字符，稍后返回
        if (--d[p].second == 0) {  // 先把当前段的次数减一；减到 0 说明这一段用光了
            ++p;  // 指针后移，指向下一段字符
        }  // 段切换判断结束
        return ans;  // 返回取到的字符
    }  // next 结束

    bool hasNext() {  // 判断是否还有字符可取
        return p < d.size() && d[p].second > 0;  // 指针未越界且当前段还有剩余次数时才算有下一个字符
    }  // hasNext 结束

private:  // 以下为内部状态，不对外暴露
    vector<pair<char, int>> d;  // 预解析结果：每项存「字符，剩余次数」
    int p = 0;  // 当前正在消耗的段下标
};  // 类定义结束

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */