
#include "google/cloud/kms/key_management_client.h"
#include "google/cloud/project.h"
#include <iostream>

using google::cloud::Options;
using google::cloud::StatusOr;
using google::cloud::kms::KeyManagementServiceClient;
using google::cloud::kms::v1::EncryptRequest;
using google::cloud::kms::v1::DecryptResponse;

int main(int argc, char* argv[]) try {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << "keyname (projects/[projectID]/locations/[location]]/keyRings/[keyring]/cryptoKeys/[key])\n";
    return 1;
  }
 
  namespace kms = ::google::cloud::kms;
  auto client = kms::KeyManagementServiceClient(kms::MakeKeyManagementServiceConnection());

  google::cloud::kms::v1::EncryptRequest request;
  request.set_name(argv[1]);
      
  std::string s = "A";
 
  request.set_plaintext(s.c_str());

  std::cout << "encrypting\n";

  auto encrypt_or  = client.Encrypt(request);

  std::cout << encrypt_or.status();



  for (char ch : encrypt_or->ciphertext())
  {
      std::cout << "0x" << static_cast<unsigned int>(static_cast<unsigned char>(ch)) << ' '; 
  }


  std::cout << "\n";
  std::cout << "done\n";

  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}