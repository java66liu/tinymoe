tinymoe
=======

###English-like programming language
######with dynamic typing, multiple dispatching and build-in continuation

Here are several samples to introduce this language:

####Hello world

	module hello world
	using standard library

	sentence print (message)
		redirect to "printf"
	end
	
	phrase sum from (start) to (end)
		set the result to 0
		repeat with the current number from start to end
			add the current number to the result
		end
	end
	
	phrase main
		print "1+ ... +100 = " & sum from 1 to 100
	end

####Geometry (Multiple dispatching)

	module geometry
	using standard library

	phrase square root of (number)
		redirect to "sqrt"
	end

	sentence print (message)
		redirect to "printf"
	end

	type rectangle
		width
		height
	end

	type triangle
		a
		b
		c
	end

	type circle
		radius
	end

	phrase area of (shape)
		raise "This is not a shape."
	end

	phrase area of (shape : rectangle)
		set the result to field width of shape * field height of shape
	end

	phrase area of (shape : triangle)
		set a to field a of shape
		set b to field b of shape
		set c to field c of shape
		set p to (a + b + c) / 2
		set the result to square root of (p * (p - a) * (p - b) * (p - c))
	end

	phrase area of (shape : circle)
		set r to field radius of shape
		set the result to r * r * 3.14
	end

	phrase (a) and (b) is the same shape
		set the result to false
	end

	phrase (a : rectangle) and (b : rectangle) is the same shape
		set the result to true
	end

	phrase (a : triangle) and (b : triangle) is the same shape
		set the result to true
	end

	phrase (a : circle) and (b : circle) is the same shape
		set the result to true
	end

	phrase main
		set shape one to new triangle of (2, 3, 4)
		set shape two to new rectangle of (1, 2)
		if shape one and shape two is the same shape
			print "This world is mad!"
		end
	end

####Make your own "yield return" (Build-in continuation)

	module enumerable
	using standard library

	symbol yielding return
	symbol yielding break
 
	type enumerable collection
		body
	end
 
	type collection enumerator
		current value
		continuation
	end
 
	phrase new enumerator from (enumerable)
		set the result to new collection enumerator
		set field continuation of the result to field body of enumerable
	end
 
	sentence move (enumerator) to the next
		set field current value of enumerator to null
		set state to new continuation state
		if field continuation of enumerator <> null
			call continuation field continuation of enumerator with (null)
			select field flag of state
				case yielding return
					set field current value of enumerator to field argument of state
					set field continuation of enumerator to field continuation of state
					reset continuation state state to null
				case yielding break
					set field continuation of enumerator to null
					reset continuation state state to null
			end
			if field flag of state <> null
				copy continuation state state
			end
		end
	end
 
	phrase (enumerator) reaches the end
		set the result to field continuation of enumerator = null
	end
 
	cps (state) (continuation)
	category
		inside ENUMERATING
	sentence yield return (value)
		set field flag of state to yielding return
		set field continuation of state to continuation
		set field argument of state to value
	end
 
	cps (state) (continuation)
	category
		inside ENUMERATING
	sentence yield break
		reset continuation state state to yielding break
	end
 
	cps (state)
	category
		start ENUMERATING
		closable
	block (body) create enumerable to (assignable receiver)
		set receiver to new enumerable collection
		set field body of receiver to body
	end
 
	block (sentence deal with (item)) repeat with (argument item) in (items : enumerable collection)
		set enumerator to new enumerator from numbers
		repeat
			move enumerator to the next
			deal with field current value of items
		end
	end

	sentence print (message)
		redirect to "printf"
	end
 
	phrase main
		create enumerable to numbers
			repeat with i from 1 to 10
				print "Enumerating " & i
				yield return i
			end
			yield break
		end
    
		repeat with number in numbers
			if number >= 5
				break
			end
		end
	end