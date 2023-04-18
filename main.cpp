/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:48:01 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/17 20:51:38 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>  // input output library

int main()
{
	int favorite_number;
	std::cout << "Tell me your favorite number: "; // standard out
	std::cin >> favorite_number; // standard in
	std::cout << "Your favorite number is " << favorite_number << std::endl;
	return 0;
}
