#include "Collision.h"
#include "../Shapes/CircleShape.h"
#include "../Body.h"
#include "../../Engine/Random.h"

namespace Collision {
    void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts) {
        for (size_t i = 0; i < bodies.size() - 1; i++) {
            for (size_t j = i + 1; j < bodies.size(); j++) {
                Body* bodyA = bodies[i];
                Body* bodyB = bodies[j];

                // Contact needs at least one dynamic body
                if (bodyA->type != Body::DYNAMIC && bodyB->type != Body::DYNAMIC) continue;

                // Check for intersection between bodies
                if (bodyA->Intersects(bodyB)) {
                    // Create contact
                    Contact contact = Collision::GenerateContact(bodyA, bodyB);
                    contacts.push_back(contact);
                }
            }
        }
    }

    Contact GenerateContact(Body* bodya, Body* bodyb) {
        Contact contact;

        contact.BodyA = bodya;
        contact.BodyB = bodyb;

        glm::vec2 Direction = bodya->Position - bodyb->Position;
        float Distance = glm::length(Direction);
        if (Distance == 0) {
            Direction = { Randomf(-0.05f, 0.05f), Randomf(-0.05f, 0.05f) };
        }

        float Radius = dynamic_cast<CircleShape*>(bodya->shape)->Radius + dynamic_cast<CircleShape*>(bodyb->shape)->Radius;
        contact.Depth = Radius - Distance;

        contact.Normal = glm::normalize(Direction);

        contact.Restitution = (bodya->Restitution + bodyb->Restitution) * 0.5f;

        return contact;
    }

    void SeparateContacts(std::vector<Contact>& contacts) {
        for (auto& Contact : contacts) {
            float TotalInverseMass = Contact.BodyA->InvMass + Contact.BodyB->InvMass;
            glm::vec2 Separation = Contact.Normal * (Contact.Depth / TotalInverseMass);

            Contact.BodyA->Position += Separation * Contact.BodyA->InvMass;
            Contact.BodyB->Position -= Separation * Contact.BodyB->InvMass;
        }
    }

    void ResolveContacts(std::vector<Contact>& contacts) {
        for (auto& Contact : contacts) {
            glm::vec2 RelativeVelocity = Contact.BodyA->Velocity - Contact.BodyB->Velocity;
            float NormalVelocity = glm::dot(RelativeVelocity, Contact.Normal);

            if (NormalVelocity > 0) continue;

            float TotalInverseMass = Contact.BodyA->InvMass + Contact.BodyB->InvMass;
            float ImpulseMagnitude = -(1 + Contact.Restitution) * NormalVelocity / TotalInverseMass;

            glm::vec2 Impulse = Contact.Normal * ImpulseMagnitude;

            Contact.BodyA->Velocity += (Impulse * Contact.BodyA->InvMass);
            Contact.BodyB->Velocity -= (Impulse * Contact.BodyB->InvMass);
        }
    }
}