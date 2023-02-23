#include "client.h"

#include <crypto.h>

#include "server.h"
Client::Client(std::string id, const Server& server) : id(id), server(&server) {
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);
    this->public_key = public_key;
    this->private_key = private_key;
}

std::string Client::get_id() { return this->id; }

std::string Client::get_publickey() { return this->public_key; }

double Client::get_wallet() {
    auto b = this->server;
    return b->get_wallet(id);
}
