#include <TaoApiCpp/util/HashMd5.h>

QString md5_q(const QString &key)
{
  QByteArray hashValue = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Md5);
  return QString(hashValue.toHex()).toUpper();
}

QString hmacMd5_q(const QString &key, const QString &message)
{
  QByteArray i_key_pad(64, '\0');
  QByteArray o_key_pad(64, '\0');

  for (int i = 0; i < 64; i++) {
    i_key_pad[i] = 0x36;
    o_key_pad[i] = 0x5C;
  }

  QByteArray actualKey = key.toLocal8Bit();

  const int blockSize = 64;

  if (actualKey.size() > blockSize)
    actualKey = QCryptographicHash::hash(actualKey, QCryptographicHash::Md5);

  for (int i = actualKey.size(); i < blockSize; i++)
    actualKey.append('\0');

  for (int i = 0; i < actualKey.size(); i++) {
    i_key_pad[i] = i_key_pad[i] ^ actualKey[i];
    o_key_pad[i] = o_key_pad[i] ^ actualKey[i];
  }

  QByteArray hashValue = QCryptographicHash::hash(o_key_pad + QCryptographicHash::hash(i_key_pad + message.toLocal8Bit(), QCryptographicHash::Md5), QCryptographicHash::Md5);
  return QString(hashValue.toHex()).toUpper();
}
