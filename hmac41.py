import hashlib
import hmac
import os

def generate_salt(length=16):
    # Generate a random salt for added security
    return os.urandom(length)

def hash_password(password, salt):
    # Hash the password using SHA-256 and the provided salt
    password_hash = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return password_hash

def create_hmac(key, message):
    # Create an HMAC using SHA-256
    h = hmac.new(key, message.encode('utf-8'), hashlib.sha256)
    return h.digest()

def main():
    # Example usage of cryptographic hash function
    password = "Shivam.R.Prajapati"
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    print("Password:", password)
    print("Salt:", salt.hex())  # Convert salt to a hex string for readability
    print("Hashed Password:", hashed_password.hex())  # Convert hashed password to a hex string for readability

    # Example usage of HMAC
    secret_key = b'secret_key'
    message = "Hello, HMAC!"
    hmac_result = create_hmac(secret_key, message)
    
    print("HMAC:", hmac_result.hex())  # Convert HMAC result to a hex string for readability

if __name__ == "__main__":
    main()
