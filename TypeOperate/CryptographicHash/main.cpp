#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDebug>

int main(int argc, char *argv[])
{    if(argc != 2)
    {
        qDebug() << "Usage: CryptographicHash <data>";
        return -1;
    }
    QByteArray byteArray(argv[1]);
    QByteArray hashRet = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);
    qDebug() << hashRet.toHex();

     return 0;
}

//QCryptographicHash类提供了生成密码散列的方法。该类可以用于生成二进制或文本数据的加密散列值。
//MD5与SHA-1比较
//二者均由MD4导出，所以SHA-1和MD5很相似。他们的强度和其它特性也很相似，但还有以下几点不同：
//对强性攻击的安全性：最显著和最重要的区别是SHA-1摘要比MD5要长32位。
//使用强行技术，产生任何一个 报文使其摘要等于给定报文摘要的难度对MD5为2^128数量级操作，而对SHA-1则是2^160数量级操作。
//这样，SHA-1对强攻击有更大的优势。
//对密码分析的安全性：由于MD5的设计，易受密码分析的攻击，相比之下，SHA-1则不然。
//速度：相同硬件上，SHA-1运行速度比MD5慢。
//碰撞：由于HASH函数产生定长的密文，结果是有限集合。而待处理的明文可以是计算机网络传输的任何信息。
//也就是说，明文信息是一个无限集合，密文信息却有限，两集合之间无一一对应关系。
//总有多个不同明文产生相同密文的情况发生，这就是所谓的碰撞。

//MD5与SHA-1曾被认为是足够安全的HASH算法，早在1994就有报告称，运算能力最强的机器，平均24天就可能找到一个MD5碰撞。
//王小云教授的方法已经为短时间内找到MD5与SHA-1碰撞成为可能。虽然如此，也并不意味着两种方法就此失效，再者，也可以通过自己的手段来进一步处理。
//比如：通过MD5与SHA结合实现。将A进行MD5处理得到B，将A在进行SHA处理得到C，再将B与C结合（比如：相加），也可把结合后的结果再进行MD5加密。
//这足以将碰撞机滤降至很小很小，所以没有绝对的安全，只有更安全。
