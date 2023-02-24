#include "client.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server) {
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);
    this->public_key = public_key;
    this->private_key = private_key;
}

std::string Client::get_id() { return this->id; }

std::string Client::get_publickey() const { return this->public_key; }

double Client::get_wallet() {
    Server* b = (Server*)(this->server);  // Server const* const server;
    return b->get_wallet(id);
}

std::string Client::sign(std::string txt) const {
    return crypto::signMessage(this->private_key, txt);
}

std::string clean(double value) {
    std::string fakeString = std::to_string(value);
    if (fakeString.find(".") == std::string::npos) {
        return fakeString;
    }

    int i = fakeString.length() - 1;
    while (fakeString.at(i) == '0' && i >= fakeString.find(".")) {
        i--;
    }
    if (fakeString.at(i) == '.') {
        return fakeString.substr(0, i);
    }
    return fakeString.substr(0, i + 1);
}

bool Client::transfer_money(std::string receiver, double value) {
    // delete useless 0

    std::string transaction = this->get_id() + "-" + receiver + "-" + clean(value);
    std::string signature = sign(this->private_key);
    if (!((Server*)(this->server))->add_pending_trx(transaction, signature))
        return false;
    return true;
}

size_t Client::generate_nonce() {
    // std::default_random_engine e;
    // std::uniform_int_distribution<int> d(0, 10);
    // size_t res = (size_t)d(e);

    return e() % 10;
}