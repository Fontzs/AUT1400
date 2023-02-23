#include "server.h"

#include <malloc.h>
#include <stdlib.h>

#include <random>
#include <stdexcept>
#include <string>

#include "client.h"
#include "crypto.h"

using std::runtime_error;

std::vector<std::string> pending_trxs;

Server::Server() { this->clients = {}; }

std::shared_ptr<Client> Server::add_client(std::string id) {
    bool isExist{false};
    std::default_random_engine e;
    std::uniform_int_distribution<int> d(1000, 10000);
    for (auto& [client, amount] : clients) {
        if (client->get_id() == id) {
            isExist == true;
            amount += d(e);
            break;
        }
    }
    if (!isExist) {
        Client* newClient = new Client(id, *this);
        std::shared_ptr<Client> sp(newClient);
        this->clients[sp] = 5;
    }
}

std::shared_ptr<Client> Server::get_client(std::string id) {
    for (auto& [k, v] : clients) {
        if (k->get_id() == id) {
            return k;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) {
    auto sp = get_client(id);
    if (sp == nullptr) {
        return 0;
    }
    return this->clients[sp];
}

bool Server::parse_trx(std::string trx, std::string sender, std::string receiver, double value) {
    int* mark = (int*)malloc(sizeof(int) * 2);
    for (int i = 0; i < trx.length(); i++) {
        if (trx.at(i) == '_') {
            throw runtime_error("something bad");
            return false;
        }
        if (trx.at(i) == '-') {
            *mark = i;
            mark++;
        }
    }
    auto mark2 = *mark;
    auto mark1 = *(mark--);
    sender = trx.substr(0, mark1);
    receiver = trx.substr(mark1 + 1, mark2);
    value = std::stod(trx.substr(mark2 + 1, trx.length()));
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) {
    std::string sender{};
    std::string receiver{};
    double value;
    parse_trx(trx, sender, receiver, value);

    if (signature != sender) {
        return false;
    }
    if (get_wallet(sender) < value) {
        return false;
    }
    pending_trxs.push_back(trx);
    return true;
}

bool isQualified(std::string str) {
    if (str.length() < 3)
        return false;
    for (int i = 0; i < str.length() - 3; i++) {
        if (str.at(i) == '0' && str.at(i + 1) == '0' && str.at(i + 2) == '0')
            return true;
    }
    return false;
}

size_t Server::mine() {
    std::string str = "";
    for (int i = 0; i < pending_trxs.size(); i++) {
        str += pending_trxs[i];
    }
    std::string id = "";
    size_t n = 0;
    for (auto& [k, v] : clients) {
        auto nonce = k->generate_nonce();
        std::string newString = str + std::to_string(nonce);
        if (isQualified(crypto::sha256(newString))) {
            std::cout << k->get_id() << std::endl;
            v += 6.5;
            n = nonce;
            break;
        }
    }
    pending_trxs.clear();
    return n;
}
